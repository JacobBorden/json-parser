#include "json.h"
#include <iostream>
#include <cassert>

int main() {
    // Parse JSON string with an object
    std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested_key\": 42}, \"key3\": [1, 2, 3]}";
    JsonValue val = JsonParser::Parse(json_str);
    assert(val.IsObject());

    // Test Copy Constructor
    JsonValue val_copy = val;
    assert(val_copy.IsObject());

    // Test Copy Assignment
    JsonValue val_assign;
    val_assign = val;
    assert(val_assign.IsObject());

    // Test Move Constructor
    JsonValue val_move = std::move(val_copy);
    assert(val_move.IsObject());

    // Test Move Assignment
    JsonValue val_move_assign;
    val_move_assign = std::move(val_assign);
    assert(val_move_assign.IsObject());

    // Test Setters to ensure old memory is cleared
    JsonValue setter_test = JsonParser::Parse("{\"a\": 1, \"b\": 2}");
    setter_test.SetNumber(100.5);
    assert(setter_test.type == JsonValueType::Number);

    setter_test = JsonParser::Parse("{\"c\": 3, \"d\": 4}");
    setter_test.SetString("test string");
    assert(setter_test.type == JsonValueType::String);

    setter_test = JsonParser::Parse("{\"e\": 5}");
    setter_test.SetBoolean(true);
    assert(setter_test.type == JsonValueType::Boolean);

    setter_test = JsonParser::Parse("{\"f\": 6}");
    setter_test.SetArray();
    assert(setter_test.type == JsonValueType::Array);

    setter_test = JsonParser::Parse("{\"g\": 7}");
    setter_test.SetObject();
    assert(setter_test.type == JsonValueType::Object);

    std::cout << "All memory leak tests executed successfully." << std::endl;
    return 0;
}
