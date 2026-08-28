#include "json.h"
#include <iostream>

int main() {
    JsonParser parser;
    std::string json_str = "{\"key1\": 123, \"key2\": {\"nested\": true}}";
    JsonValue v = parser.Parse(json_str);

    JsonValue v2 = v;
    JsonValue v3;
    v3 = v2;

    std::cout << "SUCCESS" << std::endl;
    return 0;
}
