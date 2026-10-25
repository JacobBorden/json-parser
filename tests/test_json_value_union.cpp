#include "../json.h"
#include <iostream>
#include <cassert>

void test_constructors() {
    JsonValue v1;
    assert(v1.type == JsonValueType::Null);

    JsonValue v2(JsonValueType::Number);
    v2.SetNumber(42.0);
    assert(v2.GetNumber() == 42.0);

    JsonValue v3(JsonValueType::String);
    v3.SetString("hello");
    assert(v3.GetString() == "hello");

    JsonValue v4(v3);
    assert(v4.type == JsonValueType::String);
    assert(v4.GetString() == "hello");

    JsonValue v5(std::move(v4));
    assert(v5.type == JsonValueType::String);
    assert(v5.GetString() == "hello");
    assert(v4.type == JsonValueType::Null);
}

void test_assignment_swap() {
    JsonValue v1(JsonValueType::Number);
    v1.SetNumber(3.14);

    JsonValue v2(JsonValueType::String);
    v2.SetString("world");

    v1 = v2;
    assert(v1.type == JsonValueType::String);
    assert(v1.GetString() == "world");

    JsonValue v3(JsonValueType::Array);
    v3.SetArray();
    v3.GetArray().push_back(v2);

    v1.Swap(v3);
    assert(v1.type == JsonValueType::Array);
    assert(v1.GetArray().size() == 1);
    assert(v3.type == JsonValueType::String);
    assert(v3.GetString() == "world");
}

void test_object() {
    JsonValue v(JsonValueType::Object);
    v.SetObject();
    v.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    v.GetObJect()["key1"]->SetNumber(100.0);

    JsonValue v_copy(v);
    assert(v_copy.GetObject().count("key1") == 1);
    assert(v_copy.GetObject().at("key1")->GetNumber() == 100.0);
}

int main() {
    test_constructors();
    test_assignment_swap();
    test_object();
    std::cout << "All JsonValue union tests passed." << std::endl;
    return 0;
}
