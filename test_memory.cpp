#include "json.h"
#include <iostream>

int main() {
    // 1. Test ParseObject directly (which used to leak)
    {
        std::string json_str = "{\"key\": \"value\", \"nested\": {\"inner\": 123}}";
        JsonValue parsed = JsonParser::Parse(json_str);
        if (!parsed.IsObject()) {
            std::cerr << "Expected parsed to be an object." << std::endl;
            return 1;
        }
        std::cout << "ParseObject test passed." << std::endl;
    }

    // 2. Test copy constructor
    {
        JsonValue original(JsonValueType::Object);
        original.InsertIntoObject("k1", new JsonValue(JsonValueType::Number));
        original.GetObject()["k1"]->SetNumber(42.0);

        JsonValue copy = original;
        if (copy.GetObject()["k1"]->GetNumber() != 42.0) {
            std::cerr << "Copy constructor failed." << std::endl;
            return 1;
        }
        std::cout << "Copy constructor test passed." << std::endl;
    }

    // 3. Test copy assignment
    {
        JsonValue original(JsonValueType::Object);
        original.InsertIntoObject("k2", new JsonValue(JsonValueType::String));
        original.GetObject()["k2"]->SetString("hello");

        JsonValue copy;
        copy = original;
        if (copy.GetObject()["k2"]->GetString() != "hello") {
            std::cerr << "Copy assignment failed." << std::endl;
            return 1;
        }

        // Test self-assignment
        copy = copy;
        if (copy.GetObject()["k2"]->GetString() != "hello") {
            std::cerr << "Self-assignment failed." << std::endl;
            return 1;
        }

        std::cout << "Copy assignment test passed." << std::endl;
    }

    // 4. Test move constructor
    {
        JsonValue original(JsonValueType::Object);
        original.InsertIntoObject("k3", new JsonValue(JsonValueType::Boolean));
        original.GetObject()["k3"]->SetBoolean(true);

        JsonValue moved = std::move(original);
        if (moved.GetObject()["k3"]->GetBoolean() != true) {
            std::cerr << "Move constructor failed." << std::endl;
            return 1;
        }
        if (original.type != JsonValueType::Null) {
            std::cerr << "Moved-from object not null." << std::endl;
            return 1;
        }
        std::cout << "Move constructor test passed." << std::endl;
    }

    // 5. Test move assignment
    {
        JsonValue original(JsonValueType::Object);
        original.InsertIntoObject("k4", new JsonValue(JsonValueType::Number));
        original.GetObject()["k4"]->SetNumber(99.0);

        JsonValue moved;
        moved = std::move(original);
        if (moved.GetObject()["k4"]->GetNumber() != 99.0) {
            std::cerr << "Move assignment failed." << std::endl;
            return 1;
        }
        if (original.type != JsonValueType::Null) {
            std::cerr << "Moved-from object not null." << std::endl;
            return 1;
        }
        std::cout << "Move assignment test passed." << std::endl;
    }

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
