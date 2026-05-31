#include "json.h"
#include <iostream>

int main() {
    // Basic test to see if memory leaks occur when doing object parsing and Rule of Five operations

    JsonValue val1(JsonValueType::Object);
    val1.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    val1.object_value["key1"]->SetNumber(42.0);

    // Test copy constructor
    JsonValue val2 = val1;
    if (val2.object_value["key1"]->GetNumber() != 42.0) {
        std::cerr << "Copy constructor failed." << std::endl;
        return 1;
    }

    // Test move constructor
    JsonValue val3 = std::move(val1);
    if (val3.object_value["key1"]->GetNumber() != 42.0) {
        std::cerr << "Move constructor failed." << std::endl;
        return 1;
    }
    if (val1.type != JsonValueType::Null) {
        std::cerr << "Move constructor didn't reset source type." << std::endl;
        return 1;
    }

    // Test copy assignment
    JsonValue val4;
    val4 = val2;
    if (val4.object_value["key1"]->GetNumber() != 42.0) {
        std::cerr << "Copy assignment failed." << std::endl;
        return 1;
    }

    // Test move assignment
    JsonValue val5;
    val5 = std::move(val2);
    if (val5.object_value["key1"]->GetNumber() != 42.0) {
        std::cerr << "Move assignment failed." << std::endl;
        return 1;
    }
    if (val2.type != JsonValueType::Null) {
        std::cerr << "Move assignment didn't reset source type." << std::endl;
        return 1;
    }

    std::cout << "All memory leak tests passed!" << std::endl;

    return 0;
}
