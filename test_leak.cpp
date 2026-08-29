#include "json.h"
#include <iostream>

int main() {
    {
        JsonValue val = JsonParser::Parse("{\"key\": \"value\", \"nested\": {\"a\": 1}}");
        std::cout << val.ToString() << std::endl;

        JsonValue val2 = val; // copy
        JsonValue val3 = std::move(val); // move
        val2 = val3; // assignment
    }
    return 0;
}
