#include <iostream>
#include "json.h"

int main() {
    std::string json_str = R"({"key1": "value1", "key2": 123, "nested": {"a": "b"}})";

    // Parse object
    JsonValue parsed = JsonParser::Parse(json_str);

    // Do it again to ensure things get deleted
    parsed = JsonParser::Parse(R"({"new": "val"})");

    std::cout << "Test completed." << std::endl;
    return 0;
}
