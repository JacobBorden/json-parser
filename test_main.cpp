#include <iostream>
#include "json.h"

int main() {
    try {
        JsonValue val = JsonParser::Parse("{\"hello\": 123, \"nested\": {\"key\": \"value\"}}");
        std::cout << val.ToString() << std::endl;

        JsonValue val2 = val; // Test copy constructor
        std::cout << val2.ToString() << std::endl;

        JsonValue val3;
        val3 = val; // Test copy assignment
        std::cout << val3.ToString() << std::endl;

        JsonValue val4 = std::move(val); // Test move constructor
        std::cout << val4.ToString() << std::endl;

    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
