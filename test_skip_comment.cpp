#include <iostream>
#include <cassert>
#include <string>
#include "json.h"

int main() {
    // Test case 1: Trailing single-line comment without newline
    {
        std::string json_str = "{\"key\": \"value\"} // trailing comment";
        JsonValue val = JsonParser::Parse(json_str);
        assert(val.IsObject());
    }

    // Test case 2: Unclosed block comment
    {
        std::string json_str = "{\"key\": \"value\"} /* unclosed comment";
        try {
            JsonValue val = JsonParser::Parse(json_str);
            assert(val.IsObject());
        } catch (...) {
            // It might fail during parse if index reached the end unexpectedly, but shouldn't crash
        }
    }

    // Test case 3: Comment ending exactly at string length
    {
        std::string json_str = "{} //";
        JsonValue val = JsonParser::Parse(json_str);
        assert(val.IsObject());
    }

    // Test case 4: Block comment exactly at string length
    {
        std::string json_str = "{} /* */";
        JsonValue val = JsonParser::Parse(json_str);
        assert(val.IsObject());
    }

    // Test case 5: Empty string with comment start
    {
        std::string json_str = "/";
        try {
            JsonValue val = JsonParser::Parse(json_str);
        } catch (const JsonParseException&) {
            // Expected
        }
    }

    std::cout << "All SkipComment tests passed successfully." << std::endl;
    return 0;
}
