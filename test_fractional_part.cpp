#include "json.h"
#include <iostream>
#include <cmath>

int main() {
    std::string json_str = "{\"value\": 12.34}";
    try {
        JsonValue parsed = JsonParser::Parse(json_str);
        if (!parsed.IsObject()) {
            std::cerr << "Root is not an object\n";
            return 1;
        }

        auto& obj = parsed.GetObJect();
        if (obj.find("value") == obj.end()) {
            std::cerr << "'value' key not found\n";
            return 1;
        }

        JsonValue* val = obj["value"];
        if (val->type != JsonValueType::Number) {
            std::cerr << "'value' is not a number\n";
            return 1;
        }

        if (std::abs(val->GetNumber() - 12.34) > 1e-9) {
            std::cerr << "Expected 12.34, got " << val->GetNumber() << "\n";
            return 1;
        }

        std::cout << "Test passed!\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
}
