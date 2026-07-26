#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Basic object construction and destruction
    {
        JsonValue val(JsonValueType::Object);
        val.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
        val.object_value["key1"]->number_value = 42.0;
        assert(val.object_value["key1"]->number_value == 42.0);
    } // Should not leak

    // 2. Copy Constructor
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("key1", new JsonValue(JsonValueType::Number));
        val1.object_value["key1"]->number_value = 100.0;

        JsonValue val2 = val1; // Copy construction
        assert(val2.type == JsonValueType::Object);
        assert(val2.object_value.size() == 1);
        assert(val2.object_value["key1"] != val1.object_value["key1"]); // Deep copy check
        assert(val2.object_value["key1"]->number_value == 100.0);
    } // Both should destruct cleanly

    // 3. Move Constructor
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("key1", new JsonValue(JsonValueType::String));
        val1.object_value["key1"]->string_value = "hello";

        JsonValue val2 = std::move(val1); // Move construction
        assert(val2.type == JsonValueType::Object);
        assert(val2.object_value.size() == 1);
        assert(val2.object_value["key1"]->string_value == "hello");
        assert(val1.type == JsonValueType::Null); // Moved-from state
        assert(val1.object_value.empty());
    }

    // 4. Copy Assignment
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("key1", new JsonValue(JsonValueType::Boolean));
        val1.object_value["key1"]->boolean_value = true;

        JsonValue val2(JsonValueType::Null);
        val2 = val1; // Copy assignment

        assert(val2.type == JsonValueType::Object);
        assert(val2.object_value.size() == 1);
        assert(val2.object_value["key1"] != val1.object_value["key1"]); // Deep copy check
        assert(val2.object_value["key1"]->boolean_value == true);
    }

    // 5. Move Assignment
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("key1", new JsonValue(JsonValueType::Array));

        JsonValue val2(JsonValueType::Null);
        val2 = std::move(val1); // Move assignment

        assert(val2.type == JsonValueType::Object);
        assert(val2.object_value.size() == 1);
        assert(val1.type == JsonValueType::Null); // Moved-from state
        assert(val1.object_value.empty());
    }

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
