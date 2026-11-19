#include "json.h"
#include <cmath>
#include <cfenv>
#include <clocale>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
void Check(bool ok) {
  if (!ok)
    throw std::runtime_error("check failed");
}
void Reject(const std::string &s) {
  try {
    JsonParser::Parse(s);
  } catch (const JsonParseException &) {
    return;
  }
  throw std::runtime_error("accepted invalid input: " + s);
}
int main(int argc, char **argv) {
  try {
    std::string group = argc > 1 ? argv[1] : "";
    if (group == "literals") {
      Check(JsonParser::Parse(" null ").type == JsonValueType::Null);
      Check(JsonParser::Parse("true").GetBoolean());
      Check(!JsonParser::Parse("false").GetBoolean());
    } else if (group == "numbers") {
      for (auto p : {std::pair<const char *, double>{"42", 42},
                     {"-0.45", -0.45},
                     {"1.23", 1.23},
                     {"2e3", 2000},
                     {"2E+2", 200},
                     {"1e-3", .001},
                     {"-12.5E-2", -.125}})
        Check(std::abs(JsonParser::Parse(p.first).GetNumber() - p.second) <
              1e-9);
      Check(JsonParser::Parse("1.7976931348623157e308").GetNumber() ==
            std::numeric_limits<double>::max());
      Check(JsonParser::Parse("1.7976931348623158e308").GetNumber() ==
            std::numeric_limits<double>::max());
      Check(JsonParser::Parse("-1.7976931348623158e308").GetNumber() ==
            -std::numeric_limits<double>::max());
      Check(JsonParser::Parse("2.2250738585072014e-308").GetNumber() ==
            std::numeric_limits<double>::min());
      Check(JsonParser::Parse("4.9406564584124654e-324").GetNumber() ==
            std::numeric_limits<double>::denorm_min());
      Check(JsonParser::Parse("2.2250738585072009e-308").GetNumber() ==
            std::nextafter(std::numeric_limits<double>::min(), 0.0));
      Check(JsonParser::Parse("-4.9406564584124654e-324").GetNumber() ==
            -std::numeric_limits<double>::denorm_min());
      Check(JsonParser::Parse("3e-324").GetNumber() ==
            std::numeric_limits<double>::denorm_min());
      Check(JsonParser::Parse("-3e-324").GetNumber() ==
            -std::numeric_limits<double>::denorm_min());
      const double negative_zero = JsonParser::Parse("-0").GetNumber();
      Check(negative_zero == 0.0 && std::signbit(negative_zero));
      for (const char* input : {"-0.0", "-0e10", "-0.0E-10"}) {
        const double value = JsonParser::Parse(input).GetNumber();
        Check(value == 0.0 && std::signbit(value));
      }
      for (const char* input : {"0", "0.0", "0e10"}) {
        const double value = JsonParser::Parse(input).GetNumber();
        Check(value == 0.0 && !std::signbit(value));
      }
      Reject("1e309");
      Reject("1.7976931348623159e308");
      Reject("-1.7976931348623159e308");
      Reject("2e-324");
      Reject("-2e-324");
      Reject("1e-9999");
      Reject("-1e-9999");
    } else if (group == "locale") {
      const char* current = std::setlocale(LC_NUMERIC, nullptr);
      Check(current != nullptr);
      const std::string original_locale(current);
      struct RestoreLocale {
        std::string name;
        ~RestoreLocale() { std::setlocale(LC_NUMERIC, name.c_str()); }
      } restore{original_locale};
      const char* comma_locale = std::setlocale(LC_NUMERIC, "de_DE.utf8");
      if (comma_locale == nullptr)
        comma_locale = std::setlocale(LC_NUMERIC, "de_DE.UTF-8");
      if (comma_locale == nullptr) {
        std::cerr << "Comma-decimal test requires the de_DE UTF-8 locale\n";
        return std::getenv("JSON_PARSER_REQUIRE_COMMA_LOCALE") ? 1 : 77;
      }
      Check(std::string(std::localeconv()->decimal_point) == ",");
      Check(JsonParser::Parse("1.5").GetNumber() == 1.5);
      Check(JsonParser::Parse("-12.5E-2").GetNumber() == -0.125);
      Check(JsonParser::Parse("4.9406564584124654e-324").GetNumber() ==
            std::numeric_limits<double>::denorm_min());
      const double negative_zero = JsonParser::Parse("-0.0").GetNumber();
      Check(negative_zero == 0.0 && std::signbit(negative_zero));
      Reject("1,5");
      Check(JsonParser::Parse("[1,5]").GetArray().size() == 2);
    } else if (group == "rounding") {
      const int original_rounding = std::fegetround();
      Check(original_rounding != -1);
      struct RestoreRounding {
        int mode;
        ~RestoreRounding() { std::fesetround(mode); }
      } restore{original_rounding};
      // Exact decimal integer for the binary64 overflow midpoint.
      const std::string overflow_midpoint =
          "1797693134862315807937289714053034150799341327100378269361737789"
          "8044496829276475094664901797758720709633028641669288791094655554"
          "7851940402630657488671505820681908902000708383676273854845817711"
          "5317644757302700698555713669596228429148198608349364752927190741"
          "68444365510704342711559699508093042880177904174497792";
      for (int mode : {FE_TONEAREST, FE_DOWNWARD, FE_UPWARD, FE_TOWARDZERO}) {
        Check(std::fesetround(mode) == 0);
        const double max = std::numeric_limits<double>::max();
        const double below_max = std::nextafter(max, 0.0);
        for (const char* input : {"1.7976931348623157e308"}) {
          const double value = JsonParser::Parse(input).GetNumber();
          Check(value >= below_max && value <= max);
        }
        for (const char* input : {"-1.7976931348623157e308"}) {
          const double value = JsonParser::Parse(input).GetNumber();
          Check(value <= -below_max && value >= -max);
        }
        if (mode == FE_UPWARD) Reject("1.7976931348623158e308");
        else Check(JsonParser::Parse("1.7976931348623158e308").GetNumber() == max);
        if (mode == FE_DOWNWARD) Reject("-1.7976931348623158e308");
        else Check(JsonParser::Parse("-1.7976931348623158e308").GetNumber() == -max);
        // These decimals straddle the binary64 overflow midpoint,
        // 2^1024 - 2^970, within one x86 extended-precision rounding step.
        if (mode == FE_UPWARD) Reject("1.7976931348623158079e308");
        else Check(JsonParser::Parse("1.7976931348623158079e308").GetNumber() == max);
        if (mode == FE_DOWNWARD) Reject("-1.7976931348623158079e308");
        else Check(JsonParser::Parse("-1.7976931348623158079e308").GetNumber() == -max);
        Reject("1.7976931348623158080e308");
        Reject("-1.7976931348623158080e308");
        Reject(overflow_midpoint);
        Reject("-" + overflow_midpoint);
        Check(std::fegetround() == mode);
        Reject("1e309");
        Reject("-1e309");
        Reject("1.7976931348623159e308");
        Reject("-1.7976931348623159e308");
        const double denorm = std::numeric_limits<double>::denorm_min();
        if (mode == FE_UPWARD)
          Check(JsonParser::Parse("2e-324").GetNumber() == denorm);
        else
          Reject("2e-324");
        if (mode == FE_DOWNWARD)
          Check(JsonParser::Parse("-2e-324").GetNumber() == -denorm);
        else
          Reject("-2e-324");
      }
    } else if (group == "strings") {
      Check(JsonParser::Parse(R"("hello\nworld")").GetString() ==
            "hello\nworld");
      Check(JsonParser::Parse(R"("\"\\\t")").GetString() == "\"\\\t");
      Check(JsonParser::Parse(R"("\uD834\uDD1E")").GetString() == "\xF0\x9D\x84\x9E");
    } else if (group == "arrays") {
      Check(JsonParser::Parse("[]").GetArray().empty());
      auto v = JsonParser::Parse("[1, [true, null], 2e2]");
      Check(v.GetArray().size() == 3);
      Check(v.GetArray()[1].GetArray().size() == 2);
      Check(v.GetArray()[2].GetNumber() == 200);
    } else if (group == "invalid") {
      for (auto s : {"", " ", "-", "01", "1.", "1e", "1e+", "1e9999",
                     "true false", "null!", "[", "[1", "/*", "[1,]",
                     R"("\u004z")", R"("\u 041")", R"("\uD834")",
                     R"("\uDD1E")", R"("\uD834\u0041")"})
        Reject(s);
    } else
      throw std::runtime_error("unknown group");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
