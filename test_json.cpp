#include "json.h"
#include <iostream>

void TestMemoryLeak() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested\": true}}";
    JsonValue parsed = JsonParser::Parse(json_str);

    JsonValue copied = parsed; // Test copy constructor

    JsonValue assigned;
    assigned = copied; // Test copy assignment

    JsonValue moved = std::move(parsed); // Test move constructor

    JsonValue move_assigned;
    move_assigned = std::move(copied); // Test move assignment

    std::cout << "Memory leak test complete." << std::endl;
}

int main() {
    try {
        TestMemoryLeak();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
