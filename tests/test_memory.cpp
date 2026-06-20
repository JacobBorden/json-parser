#include "../json.h"
#include <iostream>
#include <cassert>

int main() {
    std::string json = "{\"key1\": 123, \"key2\": {\"nested\": true}}";
    JsonValue parsed = JsonParser::Parse(json);
    assert(parsed.IsObject());

    // Test copy constructor
    JsonValue copied = parsed;
    assert(copied.IsObject());

    // Test copy assignment
    JsonValue assigned;
    assigned = parsed;
    assert(assigned.IsObject());

    // Test move constructor
    JsonValue moved = std::move(parsed);
    assert(moved.IsObject());

    // Test move assignment
    JsonValue move_assigned;
    move_assigned = std::move(copied);
    assert(move_assigned.IsObject());

    std::cout << "Parsed: " << moved.ToString() << std::endl;
    return 0;
}
