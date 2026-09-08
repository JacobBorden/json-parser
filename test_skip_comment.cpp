#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // Normal single-line comment
    auto v1 = JsonParser::Parse("// comment\ntrue");
    assert(v1.GetBoolean() == true);

    // Normal multi-line comment
    auto v2 = JsonParser::Parse("/* comment */ false");
    assert(v2.GetBoolean() == false);

    // Unterminated multi-line comment shouldn't crash
    try {
        JsonParser::Parse("/* unterminated");
    } catch (...) {
        // May throw parsing exception since nothing valid comes after
    }

    // Single slash shouldn't crash
    try {
        JsonParser::Parse("/");
    } catch (...) {}

    // No comment
    auto v4 = JsonParser::Parse("true");
    assert(v4.GetBoolean() == true);

    std::cout << "All SkipComment tests passed!" << std::endl;
    return 0;
}
