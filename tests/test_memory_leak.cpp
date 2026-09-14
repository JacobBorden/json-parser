#include "../json.h"
#include <iostream>
#include <stdexcept>

void Check(bool condition) {
    if (!condition) {
        throw std::runtime_error("check failed");
    }
}

void TestOwnershipOperations() {
    std::string json_str = "{\"key1\": 1, \"key2\": {\"nested\": 2}, \"key3\": [1, 2, 3]}";
    JsonValue val = JsonParser::Parse(json_str);
    JsonValue val2 = val;
    Check(val2.GetObject().at("key2") != val.GetObject().at("key2"));
    Check(val2.GetObject().at("key2")->GetObject().at("nested")->GetNumber() == 2.0);

    JsonValue val3;
    val3 = val;
    Check(val3.GetObject().at("key1") != val.GetObject().at("key1"));

    JsonValue val4 = std::move(val);
    Check(val4.GetObject().at("key1")->GetNumber() == 1.0);
    Check(val.type == JsonValueType::Null);

    val3.SetNumber(5.0);
    Check(val3.GetNumber() == 5.0);
}

void TestParseException() {
    std::string bad_json_str = "{\"key1\": 1, \"key2\": {\"nested\": 2, ";
    try {
        JsonParser::Parse(bad_json_str);
        throw std::runtime_error("expected parse exception");
    } catch (const JsonParseException&) {
        // Expected.
    }
}

void TestDuplicateObjectKey() {
    JsonValue val = JsonParser::Parse("{\"key\": 1, \"key\": 2}");
    Check(val.GetObject().size() == 1);
    Check(val.GetObject().at("key")->GetNumber() == 2.0);
}

int main() {
    try {
        for (int i = 0; i < 10000; ++i) {
            TestOwnershipOperations();
            TestParseException();
            TestDuplicateObjectKey();
        }
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }
    return 0;
}
