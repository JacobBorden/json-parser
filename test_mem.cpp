#include <iostream>
#include "json.h"

int main() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": 42, \"key3\": [1, 2, 3], \"key4\": {\"nested_key\": \"nested_value\"}}";

    // Parse the JSON string
    JsonValue val = JsonParser::Parse(json_str);

    // Create a copy to test the copy constructor
    JsonValue val_copy = val;

    // Create another copy and then move to test the move constructor
    JsonValue val_to_move = val_copy;
    JsonValue val_moved(std::move(val_to_move));

    // Test copy assignment
    JsonValue val_assigned;
    val_assigned = val_moved;

    // Output should match and val_to_move should be cleared
    std::cout << "Parse output: " << val.ToString() << std::endl;

    return 0;
}
