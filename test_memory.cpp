#include "json.h"
#include <iostream>
#include <cassert>

void testDestructor() {
    JsonValue obj(JsonValueType::Object);
    obj.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    obj.object_value["key1"]->number_value = 42;
    // When obj goes out of scope, the destructor will clean up "key1" allocation.
}

void testCopyConstructor() {
    JsonValue obj1(JsonValueType::Object);
    obj1.InsertIntoObject("key1", new JsonValue(JsonValueType::String));
    obj1.object_value["key1"]->string_value = "hello";

    JsonValue obj2(obj1); // Copy constructor
    assert(obj2.type == JsonValueType::Object);
    assert(obj2.object_value.size() == 1);
    assert(obj2.object_value["key1"]->type == JsonValueType::String);
    assert(obj2.object_value["key1"]->string_value == "hello");
    // Change obj1 to verify deep copy
    obj1.object_value["key1"]->string_value = "world";
    assert(obj2.object_value["key1"]->string_value == "hello");
}

void testMoveConstructor() {
    JsonValue obj1(JsonValueType::Object);
    obj1.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    obj1.object_value["key1"]->number_value = 100;

    JsonValue obj2(std::move(obj1)); // Move constructor
    assert(obj2.type == JsonValueType::Object);
    assert(obj2.object_value.size() == 1);
    assert(obj2.object_value["key1"]->number_value == 100);
    assert(obj1.type == JsonValueType::Null);
    assert(obj1.object_value.size() == 0);
}

void testAssignmentOperator() {
    JsonValue obj1(JsonValueType::Object);
    obj1.InsertIntoObject("key1", new JsonValue(JsonValueType::Boolean));
    obj1.object_value["key1"]->boolean_value = true;

    JsonValue obj2(JsonValueType::Null);
    obj2 = obj1; // Assignment operator (Copy)
    assert(obj2.type == JsonValueType::Object);
    assert(obj2.object_value.size() == 1);
    assert(obj2.object_value["key1"]->boolean_value == true);
    // Change obj1 to verify deep copy
    obj1.object_value["key1"]->boolean_value = false;
    assert(obj2.object_value["key1"]->boolean_value == true);

    JsonValue obj3(JsonValueType::Null);
    obj3 = std::move(obj1); // Assignment operator (Move)
    assert(obj3.type == JsonValueType::Object);
    assert(obj3.object_value.size() == 1);
    assert(obj3.object_value["key1"]->boolean_value == false);
    assert(obj1.type == JsonValueType::Null);
}

int main() {
    std::cout << "Testing memory management..." << std::endl;
    testDestructor();
    testCopyConstructor();
    testMoveConstructor();
    testAssignmentOperator();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
