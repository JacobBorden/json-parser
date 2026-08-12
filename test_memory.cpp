#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Basic destructor test (nested object)
    {
        JsonValue val(JsonValueType::Object);
        JsonValue* nested1 = new JsonValue(JsonValueType::Number);
        nested1->SetNumber(42.0);
        val.InsertIntoObject("num", nested1);

        JsonValue* nested2 = new JsonValue(JsonValueType::Object);
        JsonValue* nested3 = new JsonValue(JsonValueType::String);
        nested3->SetString("hello");
        nested2->InsertIntoObject("str", nested3);

        val.InsertIntoObject("obj", nested2);
    } // Here, `val` goes out of scope, destructor should free nested1, nested2, nested3

    // 2. Copy constructor test
    {
        JsonValue val(JsonValueType::Object);
        JsonValue* nested1 = new JsonValue(JsonValueType::Number);
        nested1->SetNumber(42.0);
        val.InsertIntoObject("num", nested1);

        JsonValue valCopy = val; // Should invoke copy constructor
        assert(valCopy.type == JsonValueType::Object);
        assert(valCopy.object_value.size() == 1);
        assert(valCopy.object_value["num"]->GetNumber() == 42.0);
        assert(valCopy.object_value["num"] != val.object_value["num"]); // Deep copy check
    }

    // 3. Assignment operator test
    {
        JsonValue val(JsonValueType::Object);
        JsonValue* nested1 = new JsonValue(JsonValueType::Number);
        nested1->SetNumber(42.0);
        val.InsertIntoObject("num", nested1);

        JsonValue valAssign(JsonValueType::Null);
        valAssign = val; // Should invoke assignment operator
        assert(valAssign.type == JsonValueType::Object);
        assert(valAssign.object_value.size() == 1);
        assert(valAssign.object_value["num"]->GetNumber() == 42.0);
        assert(valAssign.object_value["num"] != val.object_value["num"]); // Deep copy check
    }

    // 4. Move constructor test
    {
        JsonValue val(JsonValueType::Object);
        JsonValue* nested1 = new JsonValue(JsonValueType::Number);
        nested1->SetNumber(42.0);
        val.InsertIntoObject("num", nested1);

        JsonValue valMove = std::move(val); // Should invoke move constructor
        assert(valMove.type == JsonValueType::Object);
        assert(valMove.object_value.size() == 1);
        assert(valMove.object_value["num"]->GetNumber() == 42.0);
        assert(val.type == JsonValueType::Null); // Moved-from object should be empty
    }

    // 5. Move assignment test
    {
        JsonValue val(JsonValueType::Object);
        JsonValue* nested1 = new JsonValue(JsonValueType::Number);
        nested1->SetNumber(42.0);
        val.InsertIntoObject("num", nested1);

        JsonValue valMoveAssign(JsonValueType::Null);
        valMoveAssign = std::move(val); // Should invoke assignment operator (move assignment via copy-and-swap)
        assert(valMoveAssign.type == JsonValueType::Object);
        assert(valMoveAssign.object_value.size() == 1);
        assert(valMoveAssign.object_value["num"]->GetNumber() == 42.0);
        assert(val.type == JsonValueType::Null); // Moved-from object should be empty
    }

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
