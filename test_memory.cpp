#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    std::string json_str = "{\"key1\": {\"nested_key\": 123}, \"key2\": \"value2\", \"key3\": [1, 2, {\"inner_obj\": true}]}";

    try {
        JsonValue parsed_val = JsonParser::Parse(json_str);

        // Test copy constructor
        JsonValue copied_val = parsed_val;

        // Test move constructor
        JsonValue moved_val = std::move(copied_val);

        // Test copy assignment
        JsonValue assigned_val;
        assigned_val = parsed_val;

        // Test move assignment
        JsonValue move_assigned_val;
        move_assigned_val = std::move(assigned_val);

        std::cout << "Memory tests executed successfully without exceptions." << std::endl;
    } catch (const JsonParseException& e) {
        std::cerr << "JSON Parsing failed: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
