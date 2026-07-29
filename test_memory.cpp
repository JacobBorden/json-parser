#include "json.h"
#include <iostream>

int main() {
    // Create an object
    JsonValue obj1(JsonValueType::Object);

    // Insert some nested structure
    JsonValue* num = new JsonValue(JsonValueType::Number);
    num->SetNumber(42.0);
    obj1.InsertIntoObject("num", num);

    JsonValue* nested = new JsonValue(JsonValueType::Object);
    JsonValue* str = new JsonValue(JsonValueType::String);
    str->SetString("test");
    nested->InsertIntoObject("str", str);
    obj1.InsertIntoObject("nested", nested);

    // Test Copy Constructor
    JsonValue obj2 = obj1;

    // Test Move Constructor
    JsonValue obj3 = std::move(obj1);

    // Test Copy Assignment
    JsonValue obj4;
    obj4 = obj2;

    // Test Move Assignment
    JsonValue obj5;
    obj5 = std::move(obj3);

    std::cout << "Memory tests completed successfully.\n";
    return 0;
}
