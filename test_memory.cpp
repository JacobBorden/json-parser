#include "json.h"
#include <iostream>

int main() {
    std::string json_str = "{\"key\": [1, 2, 3], \"key2\": {\"nested\": true}}";
    JsonValue val = JsonParser::Parse(json_str);

    // Copy
    JsonValue val2 = val;

    // Move
    JsonValue val3 = std::move(val2);

    // Assignment
    val = val3;

    std::cout << "Test passed!" << std::endl;
    return 0;
}
