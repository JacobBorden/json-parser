#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <string>

void Check(bool condition, const std::string& msg = "check failed") {
    if (!condition) {
        throw std::runtime_error(msg);
    }
}

void TestPrettyPrint() {
    std::string json_str = "{\"key1\":1,\"key2\":[1,2,3],\"key3\":{\"nested\":2}}";
    JsonValue val = JsonParser::Parse(json_str);

    std::string minified = val.ToString(false);
    // Unordered map may result in different output ordering
    Check(minified.find("\"key1\": 1.000000") != std::string::npos || minified.find("\"key1\": 1") != std::string::npos, "Missing key1 in minified");
    Check(minified.find("\"key2\": [1.000000, 2.000000, 3.000000]") != std::string::npos || minified.find("\"key2\": [1, 2, 3]") != std::string::npos, "Missing key2 in minified");
    Check(minified.find("\"key3\": {\"nested\": 2.000000}") != std::string::npos || minified.find("\"key3\": {\"nested\": 2}") != std::string::npos, "Missing key3 in minified");

    std::string pretty = val.ToString(true);
    Check(pretty.find("{\n") != std::string::npos, "Missing opening brace and newline");
    Check(pretty.find("  \"key1\": 1.000000") != std::string::npos || pretty.find("  \"key1\": 1") != std::string::npos, "Missing or malformed key1 in pretty print");

    // Check nested array indentation
    Check(pretty.find("  \"key2\": [\n    1.000000,\n    2.000000,\n    3.000000\n  ]") != std::string::npos ||
          pretty.find("  \"key2\": [\n    1,\n    2,\n    3\n  ]") != std::string::npos, "Missing or malformed key2 in pretty print");

    // Check nested object indentation
    Check(pretty.find("  \"key3\": {\n    \"nested\": 2.000000\n  }") != std::string::npos ||
          pretty.find("  \"key3\": {\n    \"nested\": 2\n  }") != std::string::npos, "Missing or malformed key3 in pretty print");

    Check(pretty.find("\n}") != std::string::npos, "Missing closing brace and newline");
}

void TestEmptyPrettyPrint() {
    std::string empty_array = "[]";
    std::string empty_object = "{}";

    JsonValue val_arr = JsonParser::Parse(empty_array);
    JsonValue val_obj = JsonParser::Parse(empty_object);

    Check(val_arr.ToString(true) == "[]", "Empty array formatting failed");
    Check(val_obj.ToString(true) == "{}", "Empty object formatting failed");
}

int main() {
    try {
        TestPrettyPrint();
        TestEmptyPrettyPrint();
        std::cout << "All pretty print tests passed.\n";
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}
