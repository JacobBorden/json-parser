#include "json.h"
#include <iostream>

int main() {
    std::cout << "Testing memory leaks..." << std::endl;
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested_key\": 123}, \"key3\": [1, 2, 3]}";

    // Parse it in a scope so it gets destructed
    {
        JsonValue val = JsonParser::Parse(json_str);

        // Also test copy constructor
        JsonValue val2 = val;

        // Also test move assignment
        JsonValue val3;
        val3 = std::move(val2);
    }

    std::cout << "Test completed." << std::endl;
    return 0;
}
