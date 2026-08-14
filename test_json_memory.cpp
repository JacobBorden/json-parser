#include "json.h"
#include <iostream>
#include <cassert>

void test_parse_object() {
    std::string json_str = R"({"key1": "value1", "key2": 123, "key3": {"nested_key": true}})";
    JsonValue parsed = JsonParser::Parse(json_str);
    assert(parsed.IsObject());
    // Destructor of parsed should free everything properly
}

void test_copy_constructor() {
    std::string json_str = R"({"key1": "value1", "key2": 123, "key3": {"nested_key": true}})";
    JsonValue original = JsonParser::Parse(json_str);
    JsonValue copy(original);
    assert(copy.IsObject());
    assert(copy.GetObject().size() == 3);
    // original and copy destructors should free memory
}

void test_copy_assignment() {
    std::string json_str = R"({"key1": "value1"})";
    JsonValue original = JsonParser::Parse(json_str);
    JsonValue other;
    other = original;
    assert(other.IsObject());
    assert(other.GetObject().size() == 1);
}

void test_move_constructor() {
    std::string json_str = R"({"key1": "value1"})";
    JsonValue original = JsonParser::Parse(json_str);
    JsonValue moved(std::move(original));
    assert(moved.IsObject());
    assert(moved.GetObject().size() == 1);
    assert(original.type == JsonValueType::Null);
}

void test_move_assignment() {
    std::string json_str = R"({"key1": "value1"})";
    JsonValue original = JsonParser::Parse(json_str);
    JsonValue moved;
    moved = std::move(original);
    assert(moved.IsObject());
    assert(moved.GetObject().size() == 1);
    assert(original.type == JsonValueType::Null);
}

int main() {
    test_parse_object();
    test_copy_constructor();
    test_copy_assignment();
    test_move_constructor();
    test_move_assignment();
    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
