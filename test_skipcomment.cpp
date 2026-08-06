#include <iostream>
#include "json.h"

int main() {
    // Test 1: Incomplete block comment
    std::string incomplete_block = "/* This block comment never closes...";
    try {
        JsonParser::Parse(incomplete_block);
    } catch (...) {}

    // Test 2: Incomplete line comment
    std::string incomplete_line = "// This line comment ends at EOF";
    try {
        JsonParser::Parse(incomplete_line);
    } catch (...) {}

    // Test 3: Trailing slash only
    std::string trailing_slash = "/";
    try {
        JsonParser::Parse(trailing_slash);
    } catch (...) {}

    // Test 4: Only block comment opening
    std::string block_open_only = "/*";
    try {
        JsonParser::Parse(block_open_only);
    } catch (...) {}

    // Test 5: Commented out valid json (stops skipping after comment, then parses string)
    std::string comment_then_json = "/* comment */{ \"key\": \"value\" }";
    try {
        JsonValue val = JsonParser::Parse(comment_then_json);
        if (!val.IsObject()) {
            std::cerr << "Error: parsed value is not an object.\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    std::cout << "All SkipComment tests completed successfully." << std::endl;
    return 0;
}
