#include "../json.h"
#include <iostream>
#include <stdexcept>

void Check(bool condition, const std::string& msg = "") {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        JsonValue val;
        val.SetArray();
        val.GetArray().push_back(JsonValue(JsonValueType::Number));
        val.GetArray()[0].SetNumber(1.0);
        val.GetArray().push_back(JsonValue(JsonValueType::Number));
        val.GetArray()[1].SetNumber(2.0);

        std::string expected_arr = "[\n  1.000000,\n  2.000000\n]";
        Check(val.ToString(true) == expected_arr, "Pretty print array failed");

        JsonValue obj;
        obj.SetObject();
        JsonValue* v1 = new JsonValue();
        v1->SetNumber(42);
        obj.InsertIntoObject("key", v1);

        std::string expected_obj = "{\n  \"key\": 42.000000\n}";
        Check(obj.ToString(true) == expected_obj, "Pretty print object failed");

        JsonValue empty_arr;
        empty_arr.SetArray();
        Check(empty_arr.ToString(true) == "[]", "Pretty print empty array failed");

        JsonValue empty_obj;
        empty_obj.SetObject();
        Check(empty_obj.ToString(true) == "{}", "Pretty print empty object failed");

        std::cout << "All pretty print tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
