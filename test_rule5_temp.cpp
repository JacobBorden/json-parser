#include "json.h"
#include <iostream>
#include <cassert>

int main() {
    JsonValue v1(JsonValueType::Object);
    v1.object_value["test"] = new JsonValue(JsonValueType::Number);
    v1.object_value["test"]->SetNumber(42.0);

    JsonValue v2 = v1;
    assert(v2.object_value["test"]->GetNumber() == 42.0);
    v2.object_value["test"]->SetNumber(100.0);
    assert(v1.object_value["test"]->GetNumber() == 42.0); // deep copy

    JsonValue v3;
    v3 = v1;
    assert(v3.object_value["test"]->GetNumber() == 42.0);

    JsonValue v4 = std::move(v1);
    assert(v4.object_value["test"]->GetNumber() == 42.0);
    assert(v1.type == JsonValueType::Null); // v1 moved

    JsonValue v5;
    v5 = std::move(v2);
    assert(v5.object_value["test"]->GetNumber() == 100.0);
    assert(v2.type == JsonValueType::Null);

    std::cout << "OK" << std::endl;
    return 0;
}
