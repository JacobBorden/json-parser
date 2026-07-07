#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // Parse an object with nested elements
    std::string json_str = "{\"key1\": 123, \"key2\": [1, 2, 3], \"key3\": {\"nested_key\": \"nested_val\"}}";
    JsonValue val = JsonParser::Parse(json_str);

    assert(val.IsObject());

    // Test Copy Constructor
    JsonValue val_copy(val);
    assert(val_copy.IsObject());
    assert(val_copy.GetObject().size() == val.GetObject().size());
    assert(val_copy.GetObject().at("key1")->GetNumber() == val.GetObject().at("key1")->GetNumber());

    // Test Move Constructor
    JsonValue val_move(std::move(val));
    assert(val_move.IsObject());
    assert(val_move.GetObject().size() == val_copy.GetObject().size());
    // val is now moved-from, its type might be set to Null
    assert(val.type == JsonValueType::Null);

    // Test Copy Assignment
    JsonValue val_assign;
    val_assign = val_copy;
    assert(val_assign.IsObject());
    assert(val_assign.GetObject().size() == val_copy.GetObject().size());
    assert(val_assign.GetObject().at("key1")->GetNumber() == val_copy.GetObject().at("key1")->GetNumber());

    // Test Move Assignment
    JsonValue val_move_assign;
    val_move_assign = std::move(val_assign);
    assert(val_move_assign.IsObject());
    assert(val_move_assign.GetObject().size() == val_copy.GetObject().size());

    std::cout << "All memory management tests passed successfully!" << std::endl;
    return 0;
}
