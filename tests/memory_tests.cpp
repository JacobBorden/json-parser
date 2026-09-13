#include "json.h"
#include <iostream>

void Check(bool ok) {
  if (!ok)
    throw std::runtime_error("check failed");
}

int main() {
  try {
    // Test 1: Exception during ParseObject
    try {
      JsonParser::Parse(R"({"valid_key": "value", "invalid_key": })");
    } catch (const JsonParseException&) {
      // expected
    }

    // Test 2: Copy constructor
    JsonValue obj1(JsonValueType::Object);
    obj1.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    obj1.GetObJect()["key1"]->SetNumber(42.0);

    JsonValue obj2(obj1);
    Check(obj2.GetObJect()["key1"]->GetNumber() == 42.0);
    Check(obj2.GetObJect()["key1"] != obj1.GetObJect()["key1"]);

    // Test 3: Copy assignment
    JsonValue obj3(JsonValueType::Object);
    obj3.InsertIntoObject("key2", new JsonValue(JsonValueType::String));
    obj3.GetObJect()["key2"]->SetString("hello");

    obj3 = obj1;
    Check(obj3.GetObJect()["key1"]->GetNumber() == 42.0);
    Check(obj3.GetObJect()["key1"] != obj1.GetObJect()["key1"]);

    // Test 4: Move constructor
    JsonValue obj4(std::move(obj1));
    Check(obj4.GetObJect()["key1"]->GetNumber() == 42.0);
    Check(obj1.type == JsonValueType::Null);

    // Test 5: Self-assignment
    obj2 = obj2;
    Check(obj2.GetObJect()["key1"]->GetNumber() == 42.0);

  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
