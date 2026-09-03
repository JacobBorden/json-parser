#include "json.h"
#include <iostream>

void test_skip_comment() {
    bool passed = true;

    try {
        // Test 1: Single line comment at the very end (no newline)
        JsonParser::Parse("// this is a comment at the end of the string");
    } catch (...) {
        std::cerr << "Test 1 Failed: Crashed or threw on single line comment at end of string" << std::endl;
        passed = false;
    }

    try {
        // Test 2: Unclosed block comment
        JsonParser::Parse("/* this is an unclosed block comment ");
    } catch (...) {
        std::cerr << "Test 2 Failed: Crashed or threw on unclosed block comment" << std::endl;
        passed = false;
    }

    try {
        // Test 3: Normal JSON with comments
        JsonParser::Parse("// comment\n{\"key\": \"value\"}");
    } catch (...) {
        std::cerr << "Test 3 Failed: Crashed on valid JSON with comment" << std::endl;
        passed = false;
    }

    if (passed) {
        std::cout << "All tests passed successfully!" << std::endl;
    } else {
        std::cerr << "Some tests failed!" << std::endl;
        exit(1);
    }
}

int main() {
    test_skip_comment();
    return 0;
}