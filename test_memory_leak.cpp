#include "json.h"
#include <iostream>

int main() {
    // 1. Test basic allocation and destruction
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->string_value = "hello";
    }

    // 2. Test copy constructor
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->string_value = "hello";

        JsonValue v2 = v;
    }

    // 3. Test move constructor
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->string_value = "hello";

        JsonValue v3 = std::move(v);
    }

    // 4. Test copy assignment
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->string_value = "hello";

        JsonValue v4;
        v4 = v;
    }

    // 5. Test move assignment
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->string_value = "hello";

        JsonValue v5;
        v5 = std::move(v);
    }

    // 6. Test nested objects
    {
        JsonValue v(JsonValueType::Object);
        v.object_value["test"] = new JsonValue(JsonValueType::Object);
        v.object_value["test"]->object_value["inner"] = new JsonValue(JsonValueType::String);
        v.object_value["test"]->object_value["inner"]->string_value = "world";

        JsonValue v6 = v;
        JsonValue v7 = std::move(v);
        v6 = v7;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
