#include "../json.h"
#include <iostream>
#include <stdexcept>

void Check(bool condition) {
    if (!condition) {
        throw std::runtime_error("check failed");
    }
}

int main() {
    try {
        JsonValue str_val(JsonValueType::String);
        str_val.SetString("hello\n\"world\"\x01");
        Check(str_val.ToString() == "\"hello\\n\\\"world\\\"\\u0001\"");

        JsonValue obj_val(JsonValueType::Object);
        JsonValue* num_val = new JsonValue(JsonValueType::Number);
        num_val->SetNumber(42);
        obj_val.InsertIntoObject("k\ty", num_val);
        Check(obj_val.ToString() == "{\"k\\ty\": 42.000000}");
        std::cout << "All tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
