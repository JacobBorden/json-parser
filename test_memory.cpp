#include "json.h"
#include <iostream>

int main() {
    std::string json_str = R"({
        "key1": {
            "nested_key1": "value1",
            "nested_key2": 123
        },
        "key2": [1, 2, 3],
        "key3": null,
        "key4": true,
        "key5": {
            "a": { "b": { "c": 42 } }
        }
    })";

    try {
        JsonValue parsed_json = JsonParser::Parse(json_str);

        // Test copy constructor
        JsonValue copied_json = parsed_json;

        // Test move constructor
        JsonValue moved_json = std::move(copied_json);

        // Test assignment operator
        JsonValue assigned_json;
        assigned_json = moved_json;

        std::cout << "Successfully parsed, copied, moved, and assigned JSON." << std::endl;

    } catch (const JsonParseException& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
