#include "json.h"
#include <iostream>
#include <vector>

void test() {
    JsonValue v1(JsonValueType::Array);
    JsonValue v2(JsonValueType::Object);
    v2.object_value["test"] = new JsonValue(JsonValueType::Number);
    v2.object_value["test"]->SetNumber(42.0);

    v1.array_value.push_back(v2);

    JsonValue v3 = v1;
}

int main() {
    test();
    std::cout << "OK" << std::endl;
    return 0;
}
