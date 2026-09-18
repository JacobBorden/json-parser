#include "json.h"
#include <functional>
#include <iostream>
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
    } else if (group == "tostring") {
      JsonValue str_val;
      str_val.SetString("hello\nworld\"\t\\");
      Check(str_val.ToString() == R"("hello\nworld\"\t\\")");

      JsonValue obj_val;
      obj_val.SetObject();
      JsonValue* num_val = new JsonValue();
      num_val->SetNumber(1);
      obj_val.InsertIntoObject("key\n\"\t\\", num_val);
      Check(obj_val.ToString() == R"({"key\n\"\t\\": 1.000000})");
    } else
      throw std::runtime_error("unknown group");
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
