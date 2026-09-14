#include "../json.h"
#include <iostream>

void test_memory_leak() {
    std::string json_str = "{\"key1\": 1, \"key2\": {\"nested\": 2}, \"key3\": [1, 2, 3]}";
    JsonValue val = JsonParser::Parse(json_str);
    JsonValue val2 = val; // copy
    JsonValue val3;
    val3 = val; // assign
    JsonValue val4 = std::move(val);
    val3.SetNumber(5.0); // should clear
}

void test_parse_exception() {
    std::string bad_json_str = "{\"key1\": 1, \"key2\": {\"nested\": 2, ";
    try {
        JsonValue val = JsonParser::Parse(bad_json_str);
    } catch (...) {
        // Expected
    }
}

int main() {
    for (int i=0; i<10000; ++i) {
        test_memory_leak();
        test_parse_exception();
    }
    std::cout << "Tests completed" << std::endl;
    return 0;
}
