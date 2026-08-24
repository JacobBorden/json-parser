#include "json.h"
#include <iostream>

int main() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": [1, 2, 3], \"key3\": {\"nested\": true}}";

    // Parse to create initial JsonValue
    JsonValue val = JsonParser::Parse(json_str);

    // Test Copy Constructor
    JsonValue copy_val(val);

    // Test Move Constructor
    JsonValue move_val(std::move(val));

    // Test Copy Assignment
    JsonValue assign_val;
    assign_val = copy_val;

    // Test Move Assignment
    JsonValue move_assign_val;
    move_assign_val = std::move(copy_val);

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}