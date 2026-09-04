#include <iostream>
#include <cmath>
#include <cassert>
#include "json.h"

int main() {
    // Test 1: Simple fractional number
    std::string json_str1 = "1.23";
    JsonValue val1 = JsonParser::Parse(json_str1);
    std::cout << "Parsed value 1: " << val1.number_value << std::endl;
    assert(val1.type == JsonValueType::Number);
    assert(std::abs(val1.number_value - 1.23) < 1e-9);

    // Test 2: Negative fractional number
    std::string json_str2 = "-0.45";
    JsonValue val2 = JsonParser::Parse(json_str2);
    std::cout << "Parsed value 2: " << val2.number_value << std::endl;
    assert(val2.type == JsonValueType::Number);
    assert(std::abs(val2.number_value - (-0.45)) < 1e-9);

    // Test 3: Object containing a fractional number
    std::string json_str3 = "{\"val\": 3.14159}";
    JsonValue val3 = JsonParser::Parse(json_str3);
    std::cout << "Parsed value 3: " << val3.object_value["val"]->number_value << std::endl;
    assert(val3.type == JsonValueType::Object);
    assert(val3.object_value["val"]->type == JsonValueType::Number);
    assert(std::abs(val3.object_value["val"]->number_value - 3.14159) < 1e-9);

    // Memory leak cleanup since JsonValue doesn't have a destructor for object_value in this codebase currently
    delete val3.object_value["val"];

    std::cout << "All fractional tests passed." << std::endl;
    return 0;
}
