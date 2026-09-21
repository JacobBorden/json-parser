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
        JsonValue v;
        v.SetString("hello\nworld\"\\\t\x01");
        std::string s = v.ToString();
        Check(s == "\"hello\\nworld\\\"\\\\\\t\\u0001\"", "string escape failed: " + s);

        JsonValue obj;
        obj.SetObject();
        JsonValue* val = new JsonValue();
        val->SetNumber(42);
        obj.InsertIntoObject("k\ney", val);
        std::string os = obj.ToString();
        Check(os == "{\"k\\ney\": 42.000000}", "object key escape failed: " + os);

        std::cout << "All escape tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
