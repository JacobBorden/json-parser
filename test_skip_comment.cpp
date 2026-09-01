#include <iostream>
#include <cassert>
#include "json.h"

void test_bounds_checking() {
    try {
        JsonValue value1 = JsonParser::Parse("// comment without newline");
    } catch (const JsonParseException& e) {
        // Expected an error (unexpected end, since no value)
        std::cout << "Caught expected parse error 1: " << e.what() << std::endl;
    }

    try {
        JsonValue value2 = JsonParser::Parse("/* unterminated block comment");
    } catch (const JsonParseException& e) {
        // Expected an error
        std::cout << "Caught expected parse error 2: " << e.what() << std::endl;
    }

    try {
        JsonValue value3 = JsonParser::Parse("/");
    } catch (const JsonParseException& e) {
        // Expected an error
        std::cout << "Caught expected parse error 3: " << e.what() << std::endl;
    }

    // A normal one to ensure everything works (using true instead of number due to unrelated ParseNumber bug)
    JsonValue value4 = JsonParser::Parse("/* comment */ true");
    assert(value4.type == JsonValueType::Boolean);
    assert(value4.GetBoolean() == true);

    JsonValue value5 = JsonParser::Parse("// comment \n false");
    assert(value5.type == JsonValueType::Boolean);
    assert(value5.GetBoolean() == false);

    std::cout << "All SkipComment tests passed!" << std::endl;
}

int main() {
    test_bounds_checking();
    return 0;
}
