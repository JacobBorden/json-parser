#include <iostream>
#include "json.h"

int main() {
    std::string s = "{\"a\": 1, \"b\": {\"c\": 2}}";
    for(int i=0; i<100000; ++i) {
        JsonValue v = JsonParser::Parse(s);
    }
    std::cout << "Done" << std::endl;
    return 0;
}
