#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // Create a JSON string representing an object with some nested values
    std::string jsonStr = "{\"key1\": \"value1\", \"key2\": {\"nestedKey\": \"nestedValue\"}, \"key3\": [1, 2, 3]}";

    // Test parsing (allocates memory for object_value)
    JsonValue val = JsonParser::Parse(jsonStr);
    assert(val.IsObject());

    // Test copy constructor
    JsonValue valCopy(val);
    assert(valCopy.IsObject());
    assert(valCopy.GetObject().size() == val.GetObject().size());

    // Test move constructor
    JsonValue valMoved(std::move(valCopy));
    assert(valMoved.IsObject());
    assert(valMoved.GetObject().size() == val.GetObject().size());

    // Test copy assignment
    JsonValue valAssign;
    valAssign = val;
    assert(valAssign.IsObject());
    assert(valAssign.GetObject().size() == val.GetObject().size());

    // Test move assignment
    JsonValue valMoveAssign;
    valMoveAssign = std::move(valAssign);
    assert(valMoveAssign.IsObject());
    assert(valMoveAssign.GetObject().size() == val.GetObject().size());

    std::cout << "All memory management tests passed." << std::endl;
    return 0;
}
