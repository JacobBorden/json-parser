#include "../json.h"
#include <iostream>

int main() {
    try {
        JsonValue val = JsonParser::Parse("{\"a\":}");
        std::cout << "Parsed number: " << val.GetObject().at("a")->GetNumber() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << std::endl;
        return 0;
    }
}
