#include "json.h"
#include <iostream>

void test_leak() {
    std::string s = R"({"key1": {"key2": 42}})";
    JsonValue v = JsonParser::Parse(s);
}

void test_exception_leak() {
    std::string s = R"({"key1": 42, "key2": })";
    try {
        JsonValue v = JsonParser::Parse(s);
    } catch (...) {}
}

void test_duplicate_key_leak() {
    std::string s = R"({"key1": 42, "key1": 43})";
    JsonValue v = JsonParser::Parse(s);
}

int main() {
    test_leak();
    test_exception_leak();
    test_duplicate_key_leak();
    return 0;
}
