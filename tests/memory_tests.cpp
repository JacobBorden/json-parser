#include "json.h"
#include <iostream>
#include <cassert>

void check(bool ok) {
    if (!ok) throw std::runtime_error("check failed");
}

void TestRuleOf5() {
    JsonValue v1(JsonValueType::Object);
    v1.InsertIntoObject("k1", new JsonValue(JsonValueType::Number));
    v1.GetObject().at("k1")->SetNumber(42);

    // Copy Constructor
    JsonValue v2 = v1;
    check(v2.IsObject());
    check(v2.GetObject().at("k1")->GetNumber() == 42);

    // Move Constructor
    JsonValue v3 = std::move(v1);
    check(v3.IsObject());
    check(v3.GetObject().at("k1")->GetNumber() == 42);
    check(v1.GetObject().empty()); // v1 should be in valid null/empty state

    // Copy Assignment
    JsonValue v4;
    v4 = v2;
    check(v4.IsObject());
    check(v4.GetObject().at("k1")->GetNumber() == 42);

    // Move Assignment
    JsonValue v5;
    v5 = std::move(v2);
    check(v5.IsObject());
    check(v5.GetObject().at("k1")->GetNumber() == 42);
    check(v2.GetObject().empty());

    // Setter calls Clear
    v3.SetBoolean(true);
    check(v3.GetObject().empty());
    check(v3.GetBoolean() == true);
}

void TestExceptionSafety() {
    // Malformed JSON that fails mid-object parsing
    try {
        JsonParser::Parse(R"({"valid_key": 123, "invalid_value": )");
        check(false); // Should not reach here
    } catch (const JsonParseException&) {
        // Exception caught, memory leaks checked via Valgrind
    }
}

int main() {
    try {
        TestRuleOf5();
        TestExceptionSafety();
        std::cout << "All memory tests passed!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Memory test failed: " << e.what() << std::endl;
        return 1;
    }
}
