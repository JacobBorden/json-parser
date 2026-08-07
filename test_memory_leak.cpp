#include "json.h"
#include <iostream>

int main() {
    // A nested JSON object to test deep copy and destruction
    std::string json_str = "{\"key1\": {\"nestedKey\": \"nestedValue\", \"nestedNumber\": 42}, \"key2\": [1, 2, 3]}";

    try {
        JsonValue val1 = JsonParser::Parse(json_str);

        // Test copy constructor
        JsonValue val2 = val1;

        // Test assignment operator
        JsonValue val3;
        val3 = val1;

        // Test move constructor
        JsonValue val4 = std::move(val2);

        // If no memory leaks are reported by Valgrind and this completes successfully, we are good.
        std::cout << "Test completed successfully." << std::endl;
        return 0;
    } catch (const JsonParseException& e) {
        std::cerr << "JSON Parsing failed: " << e.what() << std::endl;
        return 1;
    }
}
