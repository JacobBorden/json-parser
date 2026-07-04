#include "json.h"
#include <iostream>

void TestMemoryLeak() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested_key\": 123}}";
    JsonValue val = JsonParser::Parse(json_str);

    // Copy constructor test
    JsonValue val_copy = val;

    // Assignment operator test
    JsonValue val_assign;
    val_assign = val;

    // Move constructor test
    JsonValue val_moved = std::move(val);

    // Move assignment test
    JsonValue val_move_assign;
    val_move_assign = std::move(val_assign);

    std::cout << "Parsed object: " << val_copy.ToString() << std::endl;
}

int main() {
    try {
        TestMemoryLeak();
        std::cout << "Test completed successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
