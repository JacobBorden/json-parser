# TODO

## Bugs to Fix
- **Memory Leak in `JsonValue` Object Map**: `ParseObject` allocates memory dynamically (`new JsonValue(...)`) for object values, but `JsonValue` does not have a destructor that cleans up `object_value` heap allocations. Consider using `std::unique_ptr` or adding a custom destructor, copy constructor, and assignment operator (Rule of 3/5).
- **`ParseNumber` Fractional Part Parsing Bug**: In `ParseNumber`, when checking for a decimal point (`.`), the parser does not advance the index, causing the `IsDigit` check to immediately fail and the fractional part to be ignored.
- **`ParseNumber` Exponent Parsing Bug**: Similarly, when checking for `e` or `E` in `ParseNumber`, the index is not advanced over the exponent character, causing the exponent loop to fail.
- **Missing index bounds checking**: `SkipComment` uses `json_string[index] != '\0'` which might run past the length of the string or crash if `index` is already at or past the string length. Change it to check `index < json_string.length()`.
- **Exponent parsing allows missing digits**: The exponent parser doesn't ensure there is at least one digit after `e` or `E`.

## Features and Improvements
- **Implement Tests**: Add a comprehensive testing suite (e.g. Google Test or Catch2) under a `tests/` directory to test all parsing and edge cases, especially the fixed bugs above.
- **Escape Characters in `ToString()`**: The `ToString()` method does not properly escape special characters (e.g., `\n`, `\"`, `\t`) when converting a `JsonValueType::String` back to a JSON string.
- **Refactor `JsonValue` size**: Currently `JsonValue` holds a `std::string`, `std::vector`, and `std::unordered_map` directly, making its memory footprint large for simple types. Consider using `std::variant` or a union to reduce memory usage.
- **Error Handling Details**: Add line and column numbers to `JsonParseException` for better developer experience when debugging malformed JSON.
- **Pretty Printing**: Add options to `ToString()` to support pretty-printing (with indentation and newlines) instead of only minified output.
- **UTF-8 Validation**: The parser currently assumes well-formed UTF-8/ASCII but doesn't validate surrogate pairs correctly when parsing `\uXXXX` sequences.
