#include <iostream>
#include <cassert>
#include <cmath>
#include "json.h"

int main() {
    auto v1 = JsonParser::Parse("123");
    std::cout << "v1 (123): " << v1.GetNumber() << std::endl;
    assert(v1.GetNumber() == 123);

    auto v2 = JsonParser::Parse("123.45");
    std::cout << "v2 (123.45): " << v2.GetNumber() << std::endl;
    assert(std::abs(v2.GetNumber() - 123.45) < 1e-9);

    auto v3 = JsonParser::Parse("1.2e3");
    std::cout << "v3 (1.2e3): " << v3.GetNumber() << std::endl;
    assert(std::abs(v3.GetNumber() - 1200) < 1e-9);

    auto v4 = JsonParser::Parse("-1.2E-3");
    std::cout << "v4 (-1.2E-3): " << v4.GetNumber() << std::endl;
    assert(std::abs(v4.GetNumber() - (-0.0012)) < 1e-9);

    auto v5 = JsonParser::Parse("1.2e+3");
    std::cout << "v5 (1.2e+3): " << v5.GetNumber() << std::endl;
    assert(std::abs(v5.GetNumber() - 1200) < 1e-9);

    bool threw = false;
    try {
        JsonParser::Parse("1e");
    } catch (const JsonParseException& e) {
        std::cout << "Successfully caught exception for 1e: " << e.what() << std::endl;
        threw = true;
    }
    assert(threw);

    return 0;
}
