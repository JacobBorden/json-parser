#include "json.h"
#include <iostream>
#include <cassert>

void TestParsing() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"a\": 1}}";
    JsonValue v = JsonParser::Parse(json_str);
    assert(v.type == JsonValueType::Object);
    assert(v.object_value.count("key") > 0);
    assert(v.object_value["key"]->string_value == "value");
    assert(v.object_value.count("nested") > 0);
    assert(v.object_value["nested"]->type == JsonValueType::Object);
    assert(v.object_value["nested"]->object_value["a"]->type == JsonValueType::Number);
}

void TestRuleOf5() {
    JsonValue v1(JsonValueType::Object);
    v1.object_value["a"] = new JsonValue(JsonValueType::Number);
    v1.object_value["a"]->number_value = 1.0;

    JsonValue v2 = v1; // Copy constructor
    assert(v2.type == JsonValueType::Object);
    assert(v2.object_value.count("a") > 0);
    assert(v2.object_value["a"] != v1.object_value["a"]); // Deep copy check
    assert(v2.object_value["a"]->number_value == 1.0);

    JsonValue v3;
    v3 = v1; // Copy assignment
    assert(v3.type == JsonValueType::Object);
    assert(v3.object_value.count("a") > 0);
    assert(v3.object_value["a"] != v1.object_value["a"]); // Deep copy check
    assert(v3.object_value["a"]->number_value == 1.0);

    JsonValue v4 = std::move(v1); // Move constructor
    assert(v4.type == JsonValueType::Object);
    assert(v4.object_value.count("a") > 0);
    assert(v4.object_value["a"]->number_value == 1.0);
    assert(v1.type == JsonValueType::Null); // Source is null

    JsonValue v5;
    v5 = std::move(v2); // Move assignment
    assert(v5.type == JsonValueType::Object);
    assert(v5.object_value.count("a") > 0);
    assert(v5.object_value["a"]->number_value == 1.0);
    assert(v2.type == JsonValueType::Null); // Source is null
}

int main() {
    TestParsing();
    TestRuleOf5();
    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
