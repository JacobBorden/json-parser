#include "json.h"
#include <iostream>

int main() {
    std::string json_str = "{\"key\": {\"inner\": 42}, \"array\": [1, 2, 3]}";
    JsonValue v = JsonParser::Parse(json_str);

    // Copy Constructor
    JsonValue v2 = v;

    // Default constructor + Copy Assignment
    JsonValue v3;
    v3 = v2;

    // Move Constructor
    JsonValue v4 = std::move(v3);

    // Move Assignment
    JsonValue v5;
    v5 = std::move(v4);

    std::cout << "OK" << std::endl;
    return 0;
}
