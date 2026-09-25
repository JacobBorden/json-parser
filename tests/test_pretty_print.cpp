#include "../json.h"
#include <iostream>
#include <stdexcept>
#include <string>

void Check(bool condition, const std::string& msg = "") {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        JsonValue val = JsonParser::Parse("{\"a\":1, \"b\":[true, null, {\"c\":\"hello\"}]}");
        std::string pretty_output = val.ToString(true);

        // Output could vary based on hash map ordering, we'll verify its structure somewhat, or just that it doesn't throw and formats properly.
        Check(pretty_output.find("    \"a\": 1.000000") != std::string::npos, "Missing or incorrectly indented 'a'");
        Check(pretty_output.find("    \"b\": [") != std::string::npos, "Missing or incorrectly indented 'b'");
        Check(pretty_output.find("        true,") != std::string::npos, "Missing or incorrectly indented 'true'");
        Check(pretty_output.find("        null,") != std::string::npos, "Missing or incorrectly indented 'null'");
        Check(pretty_output.find("        {") != std::string::npos, "Missing or incorrectly indented '{'");
        Check(pretty_output.find("            \"c\": \"hello\"") != std::string::npos, "Missing or incorrectly indented 'c'");
        Check(pretty_output.find("        }") != std::string::npos, "Missing or incorrectly indented '}'");
        Check(pretty_output.find("    ]") != std::string::npos, "Missing or incorrectly indented ']'");
        Check(pretty_output.find("}") != std::string::npos, "Missing '}'");

        std::cout << "All pretty print tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
