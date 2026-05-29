# Agent Instructions for `json_parser`

## Codebase Overview
This project is a minimal JSON parser written in C++11 (or later). It consists of the following key files:
- `json.h`: Contains the `JsonValue` structure, `JsonValueType` enum, and `JsonParser` static class declaration.
- `json.cpp`: Implementation of the `JsonParser` logic.
- `json_exception.h`: Definition of `JsonParseException`.

## Rules & Guidelines

### Memory Management
- `JsonValue`'s `object_value` stores raw pointers (`JsonValue*`) that are dynamically allocated during parsing (`ParseObject`). Currently, there is a known memory leak as there is no destructor. If you touch this code, be mindful of this leak and prefer replacing raw pointers with `std::unique_ptr<JsonValue>`, or at minimum, adding a proper destructor and disabling/implementing copy/assignment constructors to prevent double-frees.

### Testing
- Tests should be written using standard C++ testing frameworks (e.g. CTest is enabled in CMakeLists.txt) and should thoroughly cover edge cases (e.g., extremely large numbers, nested objects, escaped unicode sequences).
- When submitting code that alters parsing logic, you must verify the change by compiling and running tests.

### Build System
- The project uses CMake. The `CMakeLists.txt` builds a static library named `json_parser`.

### Coding Style
- Follow the existing C++ coding style:
  - Methods and Structs start with PascalCase.
  - Member variables use snake_case.
  - Variables are typically snake_case.
  - Braces are generally placed on the next line or the same line consistently as per existing code (`switch`, `while`, `if`). Keep consistent with the surrounding context.

### Focus Areas
- Refer to `TODO.MD` for known issues before writing new features.
- Special attention is needed on `ParseNumber` logic as it has some structural bugs with index advancing during fractional and exponent parsing.