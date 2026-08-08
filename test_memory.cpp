#include <iostream>
#include <cassert>
#include "json.h"

int main() {
    // 1. Basic parsing and destructor
    {
        std::string json_str = "{\"key1\": \"value1\", \"key2\": {\"nested_key\": 123}}";
        JsonValue val = JsonParser::Parse(json_str);
        assert(val.IsObject());
    } // Should not leak memory when val goes out of scope

    // 2. Copy constructor
    {
        std::string json_str = "{\"a\": 1, \"b\": [1, 2, 3]}";
        JsonValue val1 = JsonParser::Parse(json_str);
        JsonValue val2 = val1; // copy constructor

        assert(val2.IsObject());
        assert(val2.GetObject().size() == 2);
    } // Should not double free or leak

    // 3. Copy assignment
    {
        std::string json_str1 = "{\"a\": 1}";
        std::string json_str2 = "{\"b\": 2}";
        JsonValue val1 = JsonParser::Parse(json_str1);
        JsonValue val2 = JsonParser::Parse(json_str2);

        val1 = val2; // copy assignment

        assert(val1.IsObject());
        assert(val1.GetObject().count("b") == 1);
    } // Should not double free or leak

    // 4. Move constructor
    {
        std::string json_str = "{\"c\": 3}";
        JsonValue val1 = JsonParser::Parse(json_str);
        JsonValue val2 = std::move(val1); // move constructor

        assert(val2.IsObject());
        assert(val1.type == JsonValueType::Null); // State after move
    }

    // 5. Move assignment
    {
        std::string json_str1 = "{\"d\": 4}";
        std::string json_str2 = "{\"e\": 5}";
        JsonValue val1 = JsonParser::Parse(json_str1);
        JsonValue val2 = JsonParser::Parse(json_str2);

        val1 = std::move(val2); // move assignment (via copy-and-swap with move constructed argument)

        assert(val1.IsObject());
        assert(val2.type == JsonValueType::Null);
    }

    std::cout << "All memory tests passed!" << std::endl;
    return 0;
}
