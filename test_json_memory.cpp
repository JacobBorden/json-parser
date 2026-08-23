#include "json.h"
#include <iostream>
#include <cassert>

void TestParseObject() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"inner_key\": 42}}";
    JsonValue parsed_obj = JsonParser::Parse(json_str);
    assert(parsed_obj.type == JsonValueType::Object);
}

void TestCopyConstructor() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"inner_key\": 42}}";
    JsonValue parsed_obj = JsonParser::Parse(json_str);

    JsonValue copied_obj(parsed_obj);
    assert(copied_obj.type == JsonValueType::Object);
    assert(copied_obj.object_value.size() == parsed_obj.object_value.size());
}

void TestMoveConstructor() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"inner_key\": 42}}";
    JsonValue parsed_obj = JsonParser::Parse(json_str);

    JsonValue moved_obj(std::move(parsed_obj));
    assert(moved_obj.type == JsonValueType::Object);
    // original object should be nullified
    assert(parsed_obj.type == JsonValueType::Null);
    assert(parsed_obj.object_value.empty());
}

void TestCopyAssignment() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"inner_key\": 42}}";
    JsonValue parsed_obj = JsonParser::Parse(json_str);

    JsonValue assigned_obj;
    assigned_obj = parsed_obj;

    assert(assigned_obj.type == JsonValueType::Object);
    assert(assigned_obj.object_value.size() == parsed_obj.object_value.size());
}

int main() {
    std::cout << "Testing object parsing and memory safety..." << std::endl;
    TestParseObject();
    TestCopyConstructor();
    TestMoveConstructor();
    TestCopyAssignment();
    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
