#include "json.h"
#include <iostream>

int main() {
    std::string json_str = R"({"key1": {"key2": "value2"}, "key3": [1, 2, 3]})";

    {
        JsonValue val = JsonParser::Parse(json_str);
        JsonValue val2 = val;
        JsonValue val3 = std::move(val);
        val2 = val3;
        val = std::move(val2);
    }

    std::cout << "Done" << std::endl;
    return 0;
}
