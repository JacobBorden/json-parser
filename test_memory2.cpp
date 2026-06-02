#include "json.h"
#include <iostream>

void test() {
    JsonValue v1(JsonValueType::Array);
    JsonValue obj(JsonValueType::Object);
    obj.object_value["test"] = new JsonValue(JsonValueType::Number);
    obj.object_value["test"]->SetNumber(42.0);

    v1.array_value.push_back(obj);

    JsonValue v2 = v1;
    v2.array_value[0].object_value["test"]->SetNumber(100.0);

    if(v1.array_value[0].object_value["test"]->GetNumber() != 42.0) {
        std::cerr << "Shallow copy in Array!" << std::endl;
    }
}

int main() {
    test();
    std::cout << "OK" << std::endl;
    return 0;
}
