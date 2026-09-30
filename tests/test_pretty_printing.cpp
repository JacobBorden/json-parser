#include <iostream>
#include <cassert>
#include "../json.h"

int main() {
    JsonValue root;
    root.SetObject();

    JsonValue* arr = new JsonValue();
    arr->SetArray();
    arr->array_value.push_back(JsonValue(JsonValueType::Number));
    arr->array_value[0].number_value = 1;
    arr->array_value.push_back(JsonValue(JsonValueType::Number));
    arr->array_value[1].number_value = 2;

    JsonValue* empty_obj = new JsonValue();
    empty_obj->SetObject();

    root.object_value["arr"] = arr;
    root.object_value["empty"] = empty_obj;

    std::string pretty_str = root.ToString(true);

    // Check that pretty printed string contains expected newlines and spaces
    assert(pretty_str.find("{\n") == 0);
    assert(pretty_str.find("  \"arr\": [\n") != std::string::npos || pretty_str.find("  \"empty\": {}") != std::string::npos);
    assert(pretty_str.find("    1.000000,\n") != std::string::npos);
    assert(pretty_str.find("    2.000000\n") != std::string::npos);

    std::cout << "Pretty printing tests passed!" << std::endl;
    return 0;
}
