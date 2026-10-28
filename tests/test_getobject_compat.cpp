#include "../json.h"
#include <iostream>
#include <stdexcept>

void Check(bool condition, const std::string& msg = "") {
    if (!condition) {
        throw std::runtime_error("check failed: " + msg);
    }
}

int main() {
    try {
        JsonValue val(JsonValueType::Object);
        JsonValue* item = new JsonValue(JsonValueType::Number);
        item->SetNumber(42.0);
        val.InsertIntoObject("answer", item);

        // Test the new correct spelling
        auto& correctMap = val.GetObject();
        Check(correctMap.size() == 1, "GetObject failed");

        // Test the legacy compatibility spelling
        auto& legacyMap = val.GetObJect();
        Check(legacyMap.size() == 1, "GetObJect failed");

        std::cout << "GetObject compatibility tests passed." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
