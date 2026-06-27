#include <iostream>
#include "json.h"

int main() {
    std::string json = "123.45";
    JsonValue val = JsonParser::Parse(json);
    std::cout << "Parsed value: " << val.GetNumber() << std::endl;
    return 0;
}
