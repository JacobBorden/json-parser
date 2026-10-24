#include "../json.h"
#include <iostream>
#include <cassert>

void TestConstructors() {
    JsonValue v1;
    assert(v1.type == JsonValueType::Null);

    JsonValue v2(JsonValueType::String);
    assert(v2.type == JsonValueType::String);
    assert(v2.string_value == "");

    JsonValue v3(JsonValueType::Array);
    assert(v3.type == JsonValueType::Array);
    assert(v3.array_value.empty());

    JsonValue v4(JsonValueType::Object);
    assert(v4.type == JsonValueType::Object);
    assert(v4.object_value.empty());
}

void TestRuleOf5() {
    // Test Copy Constructor
    JsonValue v1(JsonValueType::String);
    v1.SetString("hello");
    JsonValue v2 = v1;
    assert(v2.type == JsonValueType::String);
    assert(v2.GetString() == "hello");

    // Test Move Constructor
    JsonValue v3 = std::move(v2);
    assert(v3.type == JsonValueType::String);
    assert(v3.GetString() == "hello");
    assert(v2.type == JsonValueType::Null);

    // Test Assignment Operator
    JsonValue v4;
    v4 = v3;
    assert(v4.type == JsonValueType::String);
    assert(v4.GetString() == "hello");

    // Test Move Assignment
    JsonValue v5;
    v5 = std::move(v4);
    assert(v5.type == JsonValueType::String);
    assert(v5.GetString() == "hello");
    assert(v4.type == JsonValueType::Null);
}

void TestSetters() {
    JsonValue v;
    v.SetString("test");
    assert(v.type == JsonValueType::String);
    assert(v.GetString() == "test");

    v.SetNumber(42.0);
    assert(v.type == JsonValueType::Number);
    assert(v.GetNumber() == 42.0);

    v.SetBoolean(true);
    assert(v.type == JsonValueType::Boolean);
    assert(v.GetBoolean() == true);

    v.SetArray();
    assert(v.type == JsonValueType::Array);
    assert(v.GetArray().empty());

    v.SetObject();
    assert(v.type == JsonValueType::Object);
    assert(v.GetObject().empty());
}

int main() {
    TestConstructors();
    TestRuleOf5();
    TestSetters();
    std::cout << "All union refactor tests passed!" << std::endl;
    return 0;
}
