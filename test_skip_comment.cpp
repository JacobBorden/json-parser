#include "json.h"
#include <iostream>

int main() {
    JsonParser parser;
    std::string json_str = "// comment\n{\"key1\": 123}";
    JsonValue v = parser.Parse(json_str);

    std::string json_str2 = "/* comment */{\"key2\": 456}";
    JsonValue v2 = parser.Parse(json_str2);

    std::cout << "SUCCESS" << std::endl;
    return 0;
}
