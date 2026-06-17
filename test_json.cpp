#include "json.h"
#include <iostream>
#include <cassert>

int main() {
    try {
        std::string json_str = R"({"key1": 1.23, "key2": {"inner": true}, "key3": [1, 2, 3], "key4": null, "key5": "str"})";
        JsonValue val = JsonParser::Parse(json_str);

        assert(val.IsObject());
        auto& obj = val.GetObJect();
        assert(obj.size() == 5);
        assert(obj["key1"]->GetNumber() == 1.23);
        assert(obj["key2"]->IsObject());
        assert(obj["key2"]->GetObJect()["inner"]->GetBoolean() == true);
        assert(obj["key3"]->IsArray());
        assert(obj["key4"]->type == JsonValueType::Null);
        assert(obj["key5"]->GetString() == "str");

        // Test copy constructor
        JsonValue val2 = val;
        assert(val2.IsObject());
        assert(val2.GetObJect()["key1"]->GetNumber() == 1.23);

        // Modify val2, val should be unchanged (deep copy)
        val2.GetObJect()["key1"]->SetNumber(4.56);
        assert(val.GetObJect()["key1"]->GetNumber() == 1.23);
        assert(val2.GetObJect()["key1"]->GetNumber() == 4.56);

        // Test move assignment
        JsonValue val3;
        val3 = std::move(val2);
        assert(val3.IsObject());
        assert(val3.GetObJect()["key1"]->GetNumber() == 4.56);

        // Output something
        std::cout << val.ToString() << std::endl;
        std::cout << "All tests passed!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
