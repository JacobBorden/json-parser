#include "../json.h"
#include <iostream>

int main() {
    std::string json = "{\"key\": {\"inner_key\": 123}, \"arr\": [{\"a\": 1}, {\"b\": 2}]}";
    JsonValue val = JsonParser::Parse(json);
    std::cout << val.ToString() << std::endl;
    JsonValue val2 = val;
    std::cout << val2.ToString() << std::endl;
    JsonValue val3;
    val3 = std::move(val2);
    std::cout << val3.ToString() << std::endl;
    return 0;
}
