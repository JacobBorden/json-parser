#include "json.h"
#include <cmath>
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
      Check(JsonParser::Parse("2.2250738585072014e-308").GetNumber() ==
            std::numeric_limits<double>::min());
      Check(JsonParser::Parse("4.9406564584124654e-324").GetNumber() ==
            std::numeric_limits<double>::denorm_min());
      const double negative_zero = JsonParser::Parse("-0").GetNumber();
      Check(negative_zero == 0.0 && std::signbit(negative_zero));
      Reject("1e309");
      Reject("1e-9999");
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
