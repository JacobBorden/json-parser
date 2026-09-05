#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // Test parsing a JSON object to check memory allocation and destruction
    std::string json_str = "{\"key1\": \"value1\", \"key2\": 42, \"key3\": [1, 2, 3], \"key4\": {\"nested\": true}}";

    // Create scope for JsonValue to test destructor automatically
    {
        JsonValue val = JsonParser::Parse(json_str);

        // Assertions to make sure it parsed correctly before it is destroyed
        assert(val.IsObject());
        assert(val.GetObject().size() == 4);

        // Test Setters which also call Clear()
        val.SetString("New String");
        assert(val.GetString() == "New String");
        assert(val.type == JsonValueType::String);
    }

    // Copy Constructor Test
    {
        JsonValue val1 = JsonParser::Parse("{\"copy\": \"test\"}");
        JsonValue val2 = val1;
        assert(val1.ToString() == val2.ToString());
    }

    // Move Constructor Test
    {
        JsonValue val1 = JsonParser::Parse("{\"move\": \"test\"}");
        JsonValue val2 = std::move(val1);
        assert(val2.IsObject());
        assert(val2.GetObject().size() == 1);
        assert(val1.type == JsonValueType::Null); // State after move
    }

    // Copy Assignment Operator Test
    {
        JsonValue val1 = JsonParser::Parse("{\"assign\": \"test\"}");
        JsonValue val2;
        val2 = val1;
        assert(val1.ToString() == val2.ToString());
    }

    std::cout << "Memory leak tests completed successfully." << std::endl;
    return 0;
}
