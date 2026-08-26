#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Create a base JsonValue object
    JsonValue root(JsonValueType::Object);

    JsonValue* child1 = new JsonValue(JsonValueType::String);
    child1->SetString("value1");

    JsonValue* child2 = new JsonValue(JsonValueType::Number);
    child2->SetNumber(42.0);

    root.InsertIntoObject("key1", child1);
    root.InsertIntoObject("key2", child2);

    assert(root.IsObject());
    assert(root.GetObject().size() == 2);
    assert(root.GetObject().at("key1")->GetString() == "value1");
    assert(root.GetObject().at("key2")->GetNumber() == 42.0);

    // 2. Test Copy Constructor
    JsonValue copy_root(root);
    assert(copy_root.IsObject());
    assert(copy_root.GetObject().size() == 2);
    // Ensure deep copy (pointers should be different)
    assert(copy_root.GetObject().at("key1") != root.GetObject().at("key1"));
    assert(copy_root.GetObject().at("key1")->GetString() == "value1");
    assert(copy_root.GetObject().at("key2")->GetNumber() == 42.0);

    // 3. Test Copy Assignment Operator
    JsonValue assign_root;
    assign_root = root;
    assert(assign_root.IsObject());
    assert(assign_root.GetObject().size() == 2);
    // Ensure deep copy
    assert(assign_root.GetObject().at("key1") != root.GetObject().at("key1"));
    assert(assign_root.GetObject().at("key1")->GetString() == "value1");

    // 4. Test Move Constructor
    JsonValue move_root(std::move(root));
    assert(move_root.IsObject());
    assert(move_root.GetObject().size() == 2);
    assert(move_root.GetObject().at("key1")->GetString() == "value1");
    // Verify original is now in Null state
    assert(root.type == JsonValueType::Null);
    assert(root.GetObject().empty());

    // 5. Test Move Assignment
    // The current implementation relies on copy-and-swap which uses the copy constructor (pass-by-value).
    // This is valid but not perfectly optimized for move semantics.
    // However, it is fully memory safe and correct according to the implemented Rule of 5 (technically 4.5 here since `operator=` takes by value).
    JsonValue move_assign_root;
    move_assign_root = std::move(move_root);

    assert(move_assign_root.IsObject());
    assert(move_assign_root.GetObject().size() == 2);
    assert(move_assign_root.GetObject().at("key1")->GetString() == "value1");
    // move_root's state is technically determined by the copy constructor (which makes a deep copy of move_root into `other` inside operator=)
    // plus the swap. So move_root gets swapped with whatever `move_assign_root` originally was (Null).
    assert(move_root.type == JsonValueType::Null);

    std::cout << "All JsonValue Rule of 5 tests passed successfully!" << std::endl;
    return 0;
}
