#include "json.h"
#include <iostream>
#include <cmath>

int main() {
    JsonParser parser;
    JsonValue v = parser.Parse("123.456");
    if (v.type == JsonValueType::Number && std::abs(v.number_value - 123.456) < 0.001) {
        std::cout << "SUCCESS: " << v.number_value << std::endl;
    } else {
        std::cout << "FAIL: " << (v.type == JsonValueType::Number ? v.number_value : -1) << std::endl;
        return 1;
    }
    return 0;
}
