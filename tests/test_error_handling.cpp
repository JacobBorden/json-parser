#include "../json.h"
#include <iostream>
#include <stdexcept>

void CheckError(const std::string& json, const std::string& expected_msg_prefix, size_t expected_line, size_t expected_col) {
    try {
        JsonParser::Parse(json);
        throw std::runtime_error("Expected parse exception for JSON:\n" + json);
    } catch (const JsonParseException& e) {
        if (e.GetLine() != expected_line || e.GetColumn() != expected_col) {
            std::cerr << "FAILED: " << e.what() << "\n";
            std::cerr << "Expected line " << expected_line << " col " << expected_col << " but got line " << e.GetLine() << " col " << e.GetColumn() << "\n";
            throw std::runtime_error("Line/col mismatch");
        }
        std::string actual_msg(e.what());
        if (actual_msg.find(expected_msg_prefix) != 0) {
            std::cerr << "FAILED: " << e.what() << "\n";
            std::cerr << "Expected prefix: " << expected_msg_prefix << "\n";
            throw std::runtime_error("Message prefix mismatch");
        }
    }
}

int main() {
    try {
        CheckError("{\n  \"a\": 1,\n  \"b\": \n}", "Expected number", 4, 1);
        CheckError("{\n  \"a\": 1\n  \"b\": 2\n}", "Expected ',' or '}' while parsing object", 3, 3);
        CheckError("[\n  1,\n  2\n  3\n]", "Expected ',' or ']' while parsing arraay", 4, 3);
        CheckError("{\n\n\n  \"a\": 1z\n}", "Expected ',' or '}' while parsing object", 4, 9);
        CheckError("{\n\"key\": \"value\\n\\uXYZW\"\n}", "Invalid Unicode escape sequence", 2, 18);
        CheckError("true\rfalse", "Unexpected trailing input", 2, 1);
        CheckError("true\nfalse", "Unexpected trailing input", 2, 1);
        CheckError("true\r\nfalse", "Unexpected trailing input", 2, 1);
        std::cout << "All error handling tests passed.\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
