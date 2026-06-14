#include "json.h"
#include <iostream>

int main() {
    std::string json_str = "{\"key\": \"value\", \"number\": 123, \"nested\": {\"inner\": true}}";
    JsonValue parsed = JsonParser::Parse(json_str);
    if (parsed.type == JsonValueType::Object) {
        std::cout << "Success!" << std::endl;
        return 0;
    }
    return 1;
}
