#include "json.h"
#include <iostream>
#include <cassert>

void TestCopyAndMove() {
    std::string json = "{\"key\": {\"inner\": 42}, \"arr\": [1, 2, 3]}";
    JsonValue val = JsonParser::Parse(json);

    // Copy construction
    JsonValue copy_val = val;
    assert(copy_val.IsObject());

    // Move construction
    JsonValue move_val = std::move(copy_val);
    assert(move_val.IsObject());
    assert(copy_val.type == JsonValueType::Null);

    // Copy assignment
    JsonValue copy_assign;
    copy_assign = val;
    assert(copy_assign.IsObject());

    // Move assignment
    JsonValue move_assign;
    move_assign = std::move(copy_assign);
    assert(move_assign.IsObject());
    assert(copy_assign.type == JsonValueType::Null);
}

void TestExceptionSafety() {
    // Malformed JSON that fails partway through parsing an object
    // This will throw when it tries to parse a string but hits unexpected end
    std::string malformed_json = "{\"key\": 123, \"bad_key\": \"bad";
    try {
        JsonValue val = JsonParser::Parse(malformed_json);
        assert(false && "Should have thrown an exception");
    } catch (const JsonParseException&) {
        // Expected exception
    }
}

int main() {
    TestCopyAndMove();
    TestExceptionSafety();
    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
