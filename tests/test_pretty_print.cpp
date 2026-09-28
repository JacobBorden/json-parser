#include <iostream>
#include <cassert>
#include "../json.h"

int main() {
    JsonValue root(JsonValueType::Object);
    root.InsertIntoObject("name", new JsonValue(JsonValueType::String));
    root.GetObJect()["name"]->SetString("John Doe");

    root.InsertIntoObject("age", new JsonValue(JsonValueType::Number));
    root.GetObJect()["age"]->SetNumber(30);

    JsonValue* arr = new JsonValue(JsonValueType::Array);
    arr->GetArray().push_back(JsonValue(JsonValueType::Number));
    arr->GetArray()[0].SetNumber(1);
    arr->GetArray().push_back(JsonValue(JsonValueType::Number));
    arr->GetArray()[1].SetNumber(2);

    root.InsertIntoObject("lucky_numbers", arr);

    std::string minified = root.ToString(false);
    std::string pretty = root.ToString(true);

    // std::cout << "Minified:\n" << minified << "\n\n";
    // std::cout << "Pretty:\n" << pretty << "\n";

    // For Object, since the order is unordered_map, we just check presence of strings
    assert(minified.find("\n") == std::string::npos);
    assert(pretty.find("\n") != std::string::npos);
    assert(pretty.find("  \"name\": \"John Doe\"") != std::string::npos || pretty.find("  \"age\": 30.000000") != std::string::npos); // some simple string check for indentation
    assert(pretty.find("  \"lucky_numbers\": [\n    1.000000,\n    2.000000\n  ]") != std::string::npos); // specific array indentation

    std::cout << "Test passed.\n";
    return 0;
}
