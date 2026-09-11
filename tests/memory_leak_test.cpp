#include "json.h"
#include <iostream>
#include <stdexcept>

void Check(bool ok, const std::string& msg = "") {
    if (!ok) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        // Test memory leak when parsing fails in the middle of an object
        try {
            JsonParser::Parse(R"({"a": 1, "b": {"c": 2, "d": }})");
        } catch (const JsonParseException&) {
            // Expected
        }

        // Test rule of 5 memory leak and double-free safety
        JsonValue val = JsonParser::Parse(R"({"a": 1, "b": {"c": 2}})");

        JsonValue val2 = val; // Copy constructor
        Check(val2.IsObject(), "val2 is object");

        JsonValue val3;
        val3 = val; // Copy assignment
        Check(val3.IsObject(), "val3 is object");

        JsonValue val4 = std::move(val2); // Move constructor
        Check(val4.IsObject(), "val4 is object");

        val4 = std::move(val3); // Move assignment
        Check(val4.IsObject(), "val4 is object again");

        // Test Set object override clears previous pointers
        val4.SetNumber(42.0);
        Check(val4.type == JsonValueType::Number, "val4 is number");
        Check(val4.GetNumber() == 42.0, "val4 equals 42");

        val4 = val; // copy again
        val4.SetArray();

        std::cout << "Memory leak tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
