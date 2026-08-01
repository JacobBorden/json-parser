#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Create a JsonValue object
    JsonValue root(JsonValueType::Object);
    root.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
    root.GetObject()["key1"]->SetNumber(10.5);

    // 2. Test copy constructor
    JsonValue copy(root);
    assert(copy.IsObject());
    assert(copy.GetObject().count("key1") == 1);
    assert(copy.GetObject().at("key1")->GetNumber() == 10.5);

    // 3. Test copy assignment
    JsonValue assign;
    assign = root;
    assert(assign.IsObject());
    assert(assign.GetObject().count("key1") == 1);
    assert(assign.GetObject().at("key1")->GetNumber() == 10.5);

    // 4. Test move constructor
    JsonValue move_constr(std::move(copy));
    assert(move_constr.IsObject());
    assert(move_constr.GetObject().count("key1") == 1);
    assert(move_constr.GetObject().at("key1")->GetNumber() == 10.5);
    // copy should be empty/null after move
    assert(copy.type == JsonValueType::Null);

    // 5. Test move assignment
    JsonValue move_assign;
    move_assign = std::move(assign);
    assert(move_assign.IsObject());
    assert(move_assign.GetObject().count("key1") == 1);
    assert(move_assign.GetObject().at("key1")->GetNumber() == 10.5);
    // assign should have moved state

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
