#include "json.h"
#include <iostream>

int main() {
    std::string json = "{\"key\": {\"inner\": 123}, \"array\": [1, 2, 3]}";

    // Parse it many times to see if memory leaks
    for(int i = 0; i < 1000; ++i) {
        JsonValue val = JsonParser::Parse(json);

        // Also test copy and assignment
        JsonValue val2 = val;
        JsonValue val3;
        val3 = val;

        // And move
        JsonValue val4 = std::move(val2);
        JsonValue val5;
        val5 = std::move(val4);
    }

    std::cout << "Memory leak test completed successfully." << std::endl;
    return 0;
}
