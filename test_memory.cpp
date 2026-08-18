#include "json.h"
#include <iostream>

int main() {
    std::string json = "{\"key\": [1, 2, {\"inner\": \"value\"}]}";
    JsonValue v = JsonParser::Parse(json);
    JsonValue v2 = v; // Copy constructor
    JsonValue v3;
    v3 = v2;          // Copy assignment
    JsonValue v4 = std::move(v2); // Move constructor
    v3 = std::move(v4); // Move assignment
    std::cout << v3.ToString() << std::endl;
    return 0;
}