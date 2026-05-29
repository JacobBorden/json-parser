# Architecture and Design

## Overview
The `json_parser` library is a straightforward, recursive descent parser for JSON strings. It parses an input string entirely in-memory and returns a `JsonValue` tree representing the JSON object.

## Components

### `JsonValue`
A variant-like type representing any valid JSON value:
- **Null**: Contains no data.
- **Boolean**: Contains a `bool`.
- **Number**: Contains a `double`.
- **String**: Contains a `std::string`.
- **Array**: Contains a `std::vector<JsonValue>`.
- **Object**: Contains a `std::unordered_map<std::string, JsonValue*>`.

It includes simple accessor/setter methods for these types and a recursive `ToString()` method to serialize the object back to a JSON string.

### `JsonParser`
A stateless class with a main entry point:
- `static JsonValue Parse(const std::string& json_string)`

Internally, it utilizes recursive descent parsing. The `ParseValue` method determines the type based on the current character (`n`, `t`, `f`, `"`, `{`, `[`, or a number) and delegates to specific parsing functions:
- `ParseNull`, `ParseBoolean`, `ParseString`, `ParseNumber`, `ParseArray`, `ParseObject`.

The parser maintains a mutable `index` representing the current cursor position in the `json_string` being parsed.

### Error Handling
The parser uses C++ exceptions. The `JsonParseException` class (derived from `std::exception`) is thrown whenever the parser encounters malformed JSON, such as unexpected characters or truncated inputs.

## Design Decisions
- **In-Memory Parsing**: The parser currently only accepts an entire string, meaning it loads the whole JSON structure into memory at once. It is not a streaming parser. This favors simplicity but increases memory footprint for large JSON files.
- **Numbers as Doubles**: All JSON numbers are parsed and stored as `double`. There is no distinction between integer and floating-point types internally.
- **Raw Pointers in Objects**: Objects store their values as dynamically allocated `JsonValue*` pointers. This avoids incomplete type errors and excessive copying but requires careful memory management. (See `TODO.MD` for pending memory leak fixes regarding this).

## Future Design Considerations
- **`std::variant`**: Transitioning `JsonValue` to use `std::variant` for its internal storage would dramatically reduce its memory footprint and eliminate the need for manual dynamic allocations and raw pointers in object maps.
- **Streaming Support**: For larger datasets, implementing a SAX-style (Simple API for XML/JSON) streaming parser in addition to the current DOM-style parser could be beneficial.