#include "../json.h"
#include <iostream>
#include <stdexcept>

void Check(bool condition) {
    if (!condition) {
        throw std::runtime_error("check failed");
    }
}

void TestAliasing() {
    JsonValue v(JsonValueType::String);
    v.SetString("hello");
    std::string& ref = v.GetString();
    v.SetString(ref); // Self-aliasing check
    Check(v.GetString() == "hello");
}

int main() {
    try {
        TestAliasing();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
