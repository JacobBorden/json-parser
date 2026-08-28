# TODO

## Bugs to Fix

## Features and Improvements
- **Implement Tests**: Add a comprehensive testing suite (e.g. Google Test or Catch2) under a `tests/` directory to test all parsing and edge cases, especially the fixed bugs above.
- **Escape Characters in `ToString()`**: The `ToString()` method does not properly escape special characters (e.g., `\n`, `\"`, `\t`) when converting a `JsonValueType::String` back to a JSON string.
- **Refactor `JsonValue` size**: Currently `JsonValue` holds a `std::string`, `std::vector`, and `std::unordered_map` directly, making its memory footprint large for simple types. Consider using `std::variant` or a union to reduce memory usage.
- **Error Handling Details**: Add line and column numbers to `JsonParseException` for better developer experience when debugging malformed JSON.
- **Pretty Printing**: Add options to `ToString()` to support pretty-printing (with indentation and newlines) instead of only minified output.
- **UTF-8 Validation**: The parser currently assumes well-formed UTF-8/ASCII but doesn't validate surrogate pairs correctly when parsing `\uXXXX` sequences.
