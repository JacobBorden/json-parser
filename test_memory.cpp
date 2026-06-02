#include "json.h"
#include <iostream>

void test() {
    JsonValue v1(JsonValueType::Array);
    v1.array_value.push_back(JsonValue(JsonValueType::Number));
    v1.array_value.back().SetNumber(42.0);

    JsonValue v2 = v1;
    v2.array_value[0].SetNumber(100.0);
    if(v1.array_value[0].GetNumber() != 42.0) {
        std::cerr << "Shallow copy in Array!" << std::endl;
    }
}

int main() {
    test();
    std::cout << "OK" << std::endl;
    return 0;
}
