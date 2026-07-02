#include <iostream>
#include "json.h"

int main() {
    std::string json_str = "{\"key\": \"value\", \"nested\": {\"key2\": 123}}";
    JsonValue parsed = JsonParser::Parse(json_str);
    std::cout << parsed.ToString() << std::endl;
    return 0;
}
