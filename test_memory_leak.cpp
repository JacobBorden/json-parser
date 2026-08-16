#include "json.h"
#include <iostream>
#include <cassert>

int main() {
    std::string json = "{\"key\": \"value\", \"obj\": {\"a\": 1, \"b\": [1, 2, 3]}}";

    // Parse JSON
    JsonValue v1 = JsonParser::Parse(json);

    // Test Copy Constructor
    JsonValue v2 = v1;
    assert(v2.IsObject());

    // Test Copy Assignment
    JsonValue v3;
    v3 = v2;
    assert(v3.IsObject());

    // Test Move Constructor
    JsonValue v4 = std::move(v3);
    assert(v4.IsObject());
    assert(v3.type == JsonValueType::Null); // After move

    // Test Move Assignment
    JsonValue v5;
    v5 = std::move(v4);
    assert(v5.IsObject());
    assert(v4.type == JsonValueType::Null); // After move (via swap)

    std::cout << "Memory leak tests completed. Run under valgrind to check for leaks." << std::endl;
    return 0;
}
