#include "json.h"
#include <iostream>

int main() {
    JsonValue val = JsonParser::Parse("{\"a\": 1, \"b\": [1, 2]}");
    JsonValue val2 = val;
    std::cout << val2.ToString() << std::endl;
    return 0;
}
