#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <string>

void Check(bool condition, const std::string& msg) {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        // Test String Serialization
        JsonValue str_val(JsonValueType::String);
        str_val.SetString("hello\n\"world\"\t\b\f\r\\\x01");
        std::string expected_str = "\"hello\\n\\\"world\\\"\\t\\b\\f\\r\\\\\\u0001\"";
        Check(str_val.ToString() == expected_str, "String serialization failed");

        // Test Object Key Serialization
        JsonValue obj_val(JsonValueType::Object);
        JsonValue* inner_val = new JsonValue(JsonValueType::Number);
        inner_val->SetNumber(42.0);
        obj_val.InsertIntoObject("key\n", inner_val);
        // Note: Number formatting in ToString() uses std::to_string, which adds trailing zeros (e.g., 42.000000)
        std::string expected_obj = "{\"key\\n\": " + std::to_string(42.0) + "}";
        Check(obj_val.ToString() == expected_obj, "Object key serialization failed. Expected: " + expected_obj + ", Got: " + obj_val.ToString());

        std::cout << "Serialization tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
