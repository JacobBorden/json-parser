#include "json.h"
#include <iostream>

void test_parse_object() {
    std::string json_str = "{\"key1\": 123, \"key2\": \"value\", \"key3\": {\"nested\": true}}";
    JsonValue val = JsonParser::Parse(json_str);
    // Should not leak when it goes out of scope.
}

void test_copy_constructor() {
    std::string json_str = "{\"key1\": true}";
    JsonValue val1 = JsonParser::Parse(json_str);
    JsonValue val2(val1);

    // Check deep copy
    val1.object_value["key1"]->boolean_value = false;
    if (val2.object_value["key1"]->boolean_value != true) {
        std::cerr << "Copy constructor did not perform a deep copy correctly!" << std::endl;
        exit(1);
    }
}

void test_assignment_operator() {
    std::string json_str = "{\"key1\": true}";
    JsonValue val1 = JsonParser::Parse(json_str);
    JsonValue val2(JsonValueType::Null);
    val2 = val1;

    // Check deep copy
    val1.object_value["key1"]->boolean_value = false;
    if (val2.object_value["key1"]->boolean_value != true) {
        std::cerr << "Assignment operator did not perform a deep copy correctly!" << std::endl;
        exit(1);
    }
}

void test_move_constructor() {
    std::string json_str = "{\"key1\": true}";
    JsonValue val1 = JsonParser::Parse(json_str);
    JsonValue val2(std::move(val1));

    if (val2.object_value.find("key1") == val2.object_value.end()) {
        std::cerr << "Move constructor failed!" << std::endl;
        exit(1);
    }
}

int main() {
    test_parse_object();
    test_copy_constructor();
    test_assignment_operator();
    test_move_constructor();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
