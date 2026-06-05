#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Test Copy Constructor
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("test", new JsonValue(JsonValueType::Number));
        val1.GetObject().at("test")->SetNumber(42.0);

        JsonValue val2(val1); // Copy constructor
        assert(val2.IsObject());
        assert(val2.GetObject().count("test") == 1);
        assert(val2.GetObject().at("test")->GetNumber() == 42.0);

        // Verify it's a deep copy
        val2.GetObject().at("test")->SetNumber(100.0);
        assert(val1.GetObject().at("test")->GetNumber() == 42.0);
    } // destructors called here

    // 2. Test Move Constructor
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("test", new JsonValue(JsonValueType::String));
        val1.GetObject().at("test")->SetString("hello");

        JsonValue val2(std::move(val1)); // Move constructor
        assert(val2.IsObject());
        assert(val2.GetObject().count("test") == 1);
        assert(val2.GetObject().at("test")->GetString() == "hello");

        // After move, val1 should be conceptually empty or invalid depending on implementation
        // Our implementation sets other.type to Null
        assert(val1.type == JsonValueType::Null);
    } // destructors called here

    // 3. Test Copy Assignment
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("test", new JsonValue(JsonValueType::Boolean));
        val1.GetObject().at("test")->SetBoolean(true);

        JsonValue val2;
        val2 = val1; // Copy assignment

        assert(val2.IsObject());
        assert(val2.GetObject().count("test") == 1);
        assert(val2.GetObject().at("test")->GetBoolean() == true);

        // Verify it's a deep copy
        val2.GetObject().at("test")->SetBoolean(false);
        assert(val1.GetObject().at("test")->GetBoolean() == true);
    }

    // 4. Test Move Assignment
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("test", new JsonValue(JsonValueType::Number));
        val1.GetObject().at("test")->SetNumber(123.4);

        JsonValue val2;
        val2 = std::move(val1); // Move assignment

        assert(val2.IsObject());
        assert(val2.GetObject().count("test") == 1);
        assert(val2.GetObject().at("test")->GetNumber() == 123.4);

        // After move, val1 should be null
        assert(val1.type == JsonValueType::Null);
    }

    // 5. Test Copy Assignment overwriting existing object data (to ensure ClearObject is called)
    {
        JsonValue val1(JsonValueType::Object);
        val1.InsertIntoObject("v1", new JsonValue(JsonValueType::Number));

        JsonValue val2(JsonValueType::Object);
        val2.InsertIntoObject("v2", new JsonValue(JsonValueType::String));

        val2 = val1;
        assert(val2.GetObject().count("v1") == 1);
        assert(val2.GetObject().count("v2") == 0);
    }

    std::cout << "All JsonValue Rule of Five tests passed!" << std::endl;
    return 0;
}
