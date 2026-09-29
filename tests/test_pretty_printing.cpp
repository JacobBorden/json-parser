#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <cmath>

void Check(bool condition, const std::string& msg = "") {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        // Test empty array and object
        JsonValue empty_arr;
        empty_arr.SetArray();
        Check(empty_arr.ToString(true) == "[]", "empty array failed: " + empty_arr.ToString(true));

        JsonValue empty_obj;
        empty_obj.SetObject();
        Check(empty_obj.ToString(true) == "{}", "empty object failed: " + empty_obj.ToString(true));

        // Test array pretty printing
        JsonValue arr = JsonParser::Parse("[1, 2, 3]");
        std::string expected_arr = "[\n  1.000000,\n  2.000000,\n  3.000000\n]";
        Check(arr.ToString(true) == expected_arr, "array pretty printing failed:\n" + arr.ToString(true));

        // Test object pretty printing
        JsonValue obj = JsonParser::Parse("{\"a\": 1, \"b\": 2}");
        std::string obj_str = obj.ToString(true);
        // Due to unordered_map, the order of keys is not guaranteed.
        // We will just parse it back and make sure it has the same values and check for basic structure
        Check(obj_str.find("{\n") == 0, "object pretty printing should start with {\n");
        Check(obj_str.find("\n}") != std::string::npos, "object pretty printing should end with \n}");
        Check(obj_str.find("  \"a\": 1.000000") != std::string::npos, "object pretty printing should contain \"a\": 1.000000");
        Check(obj_str.find("  \"b\": 2.000000") != std::string::npos, "object pretty printing should contain \"b\": 2.000000");

        // Test nested structure
        JsonValue nested = JsonParser::Parse("{\"a\": [1, {}]}");
        std::string nested_str = nested.ToString(true);
        std::string expected_nested = "{\n  \"a\": [\n    1.000000,\n    {}\n  ]\n}";
        Check(nested_str == expected_nested, "nested pretty printing failed:\n" + nested_str);

        std::cout << "All pretty printing tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
