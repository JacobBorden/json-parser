#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <string>

void Check(bool condition) {
    if (!condition) {
        throw std::runtime_error("check failed");
    }
}

int main() {
    try {
        std::string bad_json_str = "{\n  \"a\": \n  }";
        JsonParser::Parse(bad_json_str);
        throw std::runtime_error("expected parse exception");
    } catch (const JsonParseException& e) {
        std::string msg = e.what();
        if (msg.find("at line 3, column 3") == std::string::npos) {
            std::cerr << "Incorrect error message: " << msg << std::endl;
            return 1;
        }
    }
    return 0;
}
