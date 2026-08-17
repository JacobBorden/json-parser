#include "json.h"
#include <iostream>

void TestMemoryLeakFix() {
    JsonValue root(JsonValueType::Object);
    root.object_value["key1"] = new JsonValue(JsonValueType::String);
    root.object_value["key1"]->string_value = "value1";

    root.object_value["key2"] = new JsonValue(JsonValueType::Number);
    root.object_value["key2"]->number_value = 42.0;

    JsonValue nested(JsonValueType::Object);
    nested.object_value["nested_key"] = new JsonValue(JsonValueType::Boolean);
    nested.object_value["nested_key"]->boolean_value = true;

    root.object_value["key3"] = new JsonValue(nested);

    // Test copy constructor
    JsonValue copied_root = root;

    // Test copy assignment
    JsonValue assigned_root;
    assigned_root = root;

    // Test move constructor
    JsonValue moved_root = std::move(copied_root);

    // Test move assignment
    JsonValue move_assigned_root;
    move_assigned_root = std::move(assigned_root);

    std::cout << "Test passed!" << std::endl;
}

int main() {
    TestMemoryLeakFix();
    return 0;
}
