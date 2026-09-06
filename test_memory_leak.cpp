#include "json.h"
#include <iostream>

int main() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested\": true}}";
    try {
        JsonValue val1 = JsonParser::Parse(json_str);

        // Test copy constructor
        JsonValue val2 = val1;

        // Test move constructor
        JsonValue val3 = std::move(val2);

        // Test copy assignment
        JsonValue val4;
        val4 = val3;

        // Output something so it doesn't just quietly succeed
        std::cout << val4.ToString() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
