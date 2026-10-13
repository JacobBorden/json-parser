#include "json.h"

#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
  try {
    const JsonValue parsed = JsonParser::Parse("{\"message\":\"hello\\nworld\",\"count\":2e1}");
    if (parsed.type != JsonValueType::Object || parsed.GetObject().size() != 2)
      throw std::runtime_error("object shape changed");
    if (parsed.GetObject().at("message")->GetString() != "hello\nworld")
      throw std::runtime_error("string value changed");
    if (parsed.GetObject().at("count")->GetNumber() != 20.0)
      throw std::runtime_error("number value changed");
    const JsonValue round_trip = JsonParser::Parse(parsed.ToString());
    if (round_trip.GetObject().at("message")->GetString() != "hello\nworld")
      throw std::runtime_error("serialization changed");
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
