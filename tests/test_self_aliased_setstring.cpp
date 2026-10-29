#include "json.h"
#include <cassert>
#include <string>
#include <iostream>

int main() {
    JsonValue val(JsonValueType::String);
    val.SetString("Initial Long String Value To Test Self Aliased Overwrite Properly Because Short Strings Use SSO");

    // Self-aliased call
    val.SetString(val.GetString());

    assert(val.GetString() == "Initial Long String Value To Test Self Aliased Overwrite Properly Because Short Strings Use SSO");
    std::cout << "Self-aliased SetString test passed." << std::endl;
    return 0;
}
