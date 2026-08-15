#include "json.h"
#include <iostream>

int main() {
    std::string json = "{\"key\": {\"inner\": \"value\"}, \"arr\": [1, 2, 3]}";
    JsonValue val = JsonParser::Parse(json);

    // Copy construction
    JsonValue val2 = val;

    // Move construction
    JsonValue val3 = std::move(val2);

    // Assignment
    JsonValue val4(JsonValueType::Null);
    val4 = val3;

    std::cout << val.ToString() << std::endl;
    return 0;
}
