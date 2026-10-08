import re

with open('json.h', 'r') as f:
    content = f.read()

# Fix default constructor
content = content.replace(
    'JsonValue(JsonValueType type_ = JsonValueType::Null) : type(JsonValueType::Null) {',
    'JsonValue(JsonValueType type_ = JsonValueType::Null) : type(JsonValueType::Null), boolean_value(false) {'
)

# Fix copy constructor
content = content.replace(
    'JsonValue(const JsonValue& other) : type(JsonValueType::Null) {',
    'JsonValue(const JsonValue& other) : type(JsonValueType::Null), boolean_value(false) {'
)

# Fix move constructor
content = content.replace(
    'JsonValue(JsonValue&& other) noexcept : type(JsonValueType::Null) {',
    'JsonValue(JsonValue&& other) noexcept : type(JsonValueType::Null), boolean_value(false) {'
)

with open('json.h', 'w') as f:
    f.write(content)

print("json.h constructors updated successfully.")
