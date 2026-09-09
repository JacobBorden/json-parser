#include <iostream>
#include "json.h"

int main() {
    std::string s = "1.2e3";
    JsonValue v = JsonParser::Parse(s);
    std::cout << v.number_value << std::endl;
    return 0;
}
