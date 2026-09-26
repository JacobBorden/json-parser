#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <cassert>
#include <string>

void Check(bool condition, const std::string& msg = "") {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        JsonValue arr(JsonValueType::Array);
        JsonValue item1(JsonValueType::Number);
        item1.SetNumber(1);
        JsonValue item2(JsonValueType::Number);
        item2.SetNumber(2);
        arr.GetArray().push_back(item1);
        arr.GetArray().push_back(item2);

        JsonValue obj(JsonValueType::Object);
        obj.InsertIntoObject("arr", new JsonValue(arr));

        JsonValue str(JsonValueType::String);
        str.SetString("hello");
        obj.InsertIntoObject("str", new JsonValue(str));

        std::string pretty = obj.ToString(true);
        std::cout << pretty << std::endl;

        // Output format could be either:
        // {
        //   "arr": [
        //     1.000000,
        //     2.000000
        //   ],
        //   "str": "hello"
        // }
        // OR unordered map means order can differ

        // Very basic check that newlines and spaces exist
        Check(pretty.find("{\n") == 0, "Missing opening { with newline");
        Check(pretty.find("\n}") != std::string::npos, "Missing closing } with newline");
        Check(pretty.find("  \"arr\": [\n") != std::string::npos || pretty.find("  \"str\": \"hello\"") != std::string::npos, "Missing expected 2 space indentation for keys");
        Check(pretty.find("    1.000000") != std::string::npos, "Missing expected 4 space indentation for array items");

        // Also check empty objects/arrays don't add unnecessary newlines
        JsonValue emptyArr(JsonValueType::Array);
        Check(emptyArr.ToString(true) == "[]", "Empty array should just be []");

        JsonValue emptyObj(JsonValueType::Object);
        Check(emptyObj.ToString(true) == "{}", "Empty object should just be {}");

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Pretty print tests passed." << std::endl;
    return 0;
}
