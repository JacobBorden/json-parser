#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // Create an object
    JsonValue root(JsonValueType::Object);

    JsonValue* child1 = new JsonValue(JsonValueType::Number);
    child1->SetNumber(42.0);
    root.InsertIntoObject("child1", child1);

    JsonValue* child2 = new JsonValue(JsonValueType::Object);
    JsonValue* grandchild = new JsonValue(JsonValueType::String);
    grandchild->SetString("hello");
    child2->InsertIntoObject("grandchild", grandchild);
    root.InsertIntoObject("child2", child2);

    // Test copy constructor
    JsonValue copy = root;
    assert(copy.type == JsonValueType::Object);
    assert(copy.object_value.size() == 2);
    assert(copy.object_value["child1"] != root.object_value["child1"]); // deep copy
    assert(copy.object_value["child1"]->GetNumber() == 42.0);

    // Test copy assignment
    JsonValue assign_copy(JsonValueType::Null);
    assign_copy = root;
    assert(assign_copy.type == JsonValueType::Object);
    assert(assign_copy.object_value.size() == 2);
    assert(assign_copy.object_value["child1"] != root.object_value["child1"]);

    // Test move constructor
    JsonValue move_copy = std::move(copy);
    assert(move_copy.type == JsonValueType::Object);
    assert(move_copy.object_value.size() == 2);
    // copy should be in a valid but unspecified state, our implementation sets to Null
    assert(copy.type == JsonValueType::Null);

    // Test move assignment
    JsonValue move_assign;
    move_assign = std::move(assign_copy);
    assert(move_assign.type == JsonValueType::Object);
    assert(move_assign.object_value.size() == 2);
    assert(assign_copy.type == JsonValueType::Null);

    // Test parser with objects (to ensure parsing doesn't leak either)
    std::string json_str = "{\"key1\": 123, \"key2\": {\"nested\": true}}";
    JsonValue parsed = JsonParser::Parse(json_str);
    assert(parsed.type == JsonValueType::Object);

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
