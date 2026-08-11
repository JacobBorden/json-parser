#include "../json.h"
#include <iostream>
#include <cassert>

void test_memory_leak() {
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nestedKey\": 42}, \"key3\": [1, 2, 3]}";

    // Parse the JSON string
    JsonValue val = JsonParser::Parse(json_str);

    // Test Copy Constructor
    JsonValue copied_val = val;
    std::cout << "copied_val: " << copied_val.ToString() << std::endl;
}

int main() {
    test_memory_leak();
    std::cout << "Memory leak tests passed." << std::endl;
    return 0;
}
