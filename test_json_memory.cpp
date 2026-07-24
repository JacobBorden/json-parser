#include "json.h"
#include <cassert>
#include <iostream>

void test_memory_leak() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested_key\": 123}, \"key3\": [1, 2, 3]}";

    // Parse
    JsonValue val = JsonParser::Parse(json_str);

    // Copy Constructor
    JsonValue copied_val = val;
    assert(copied_val.type == JsonValueType::Object);
    assert(copied_val.object_value.size() == 3);

    // Move Constructor
    JsonValue moved_val = std::move(copied_val);
    assert(moved_val.type == JsonValueType::Object);
    assert(moved_val.object_value.size() == 3);
    assert(copied_val.type == JsonValueType::Null); // State after move

    // Copy Assignment
    JsonValue assigned_val;
    assigned_val = moved_val;
    assert(assigned_val.type == JsonValueType::Object);
    assert(assigned_val.object_value.size() == 3);

    // Move Assignment
    JsonValue move_assigned_val;
    move_assigned_val = std::move(assigned_val);
    assert(move_assigned_val.type == JsonValueType::Object);
    assert(move_assigned_val.object_value.size() == 3);
    assert(assigned_val.type == JsonValueType::Null); // State after move

    std::cout << "All memory tests passed successfully." << std::endl;
}

int main() {
    try {
        test_memory_leak();
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
