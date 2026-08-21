#include <iostream>
#include <cmath>
#include "json.h"

int main() {
    int failures = 0;

    auto test_number = [&](const std::string& json_str, double expected) {
        try {
            JsonValue val = JsonParser::Parse(json_str);
            if (val.type != JsonValueType::Number) {
                std::cerr << "Test failed for " << json_str << ": Not a number type." << std::endl;
                failures++;
                return;
            }
            double actual = val.GetNumber();
            if (std::abs(actual - expected) > 1e-9) {
                std::cerr << "Test failed for " << json_str << ": Expected " << expected << ", got " << actual << std::endl;
                failures++;
            } else {
                std::cout << "Test passed for " << json_str << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Test failed for " << json_str << ": Exception thrown: " << e.what() << std::endl;
            failures++;
        }
    };

    test_number("123.45", 123.45);
    test_number("12e3", 12000.0);
    test_number("-12.5E-1", -1.25);
    test_number("1e+2", 100.0);

    if (failures > 0) {
        std::cerr << failures << " tests failed." << std::endl;
        return 1;
    }

    std::cout << "All tests passed." << std::endl;
    return 0;
}
