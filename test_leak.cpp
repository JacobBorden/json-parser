#include "json.h"
#include <iostream>
int main() {
    std::string s = "{\"a\": 1, \"b\": {\"c\": 2}}";
    JsonValue v = JsonParser::Parse(s);
    std::cout << v.ToString() << std::endl;
    return 0;
}
