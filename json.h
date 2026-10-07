#pragma once
#ifndef _JSON_
#define _JSON_
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstddef>
#include "json_exception.h"
enum class JsonValueType{
	Null,
	Boolean,
	Number,
	String,
	Array,
	Object
};


struct JsonValue{

	JsonValueType type;
	union {
		bool boolean_value;
		double number_value;
		std::string string_value;
		std::vector<JsonValue> array_value;
		std::unordered_map<std::string, JsonValue*> object_value;
	};

	JsonValue(JsonValueType type_ = JsonValueType::Null) : type(JsonValueType::Null) {
		switch (type_) {
			case JsonValueType::Boolean: new (&boolean_value) bool(false); type = JsonValueType::Boolean; break;
			case JsonValueType::Number: new (&number_value) double(0.0); type = JsonValueType::Number; break;
			case JsonValueType::String: new (&string_value) std::string(); type = JsonValueType::String; break;
			case JsonValueType::Array: new (&array_value) std::vector<JsonValue>(); type = JsonValueType::Array; break;
			case JsonValueType::Object: new (&object_value) std::unordered_map<std::string, JsonValue*>(); type = JsonValueType::Object; break;
			case JsonValueType::Null: break;
		}
	}

	~JsonValue() {
		Clear();
	}

	JsonValue(const JsonValue& other) : type(JsonValueType::Null) {
		switch (other.type) {
			case JsonValueType::Boolean: new (&boolean_value) bool(other.boolean_value); break;
			case JsonValueType::Number: new (&number_value) double(other.number_value); break;
			case JsonValueType::String: new (&string_value) std::string(other.string_value); break;
			case JsonValueType::Array: new (&array_value) std::vector<JsonValue>(other.array_value); break;
			case JsonValueType::Object: {
				new (&object_value) std::unordered_map<std::string, JsonValue*>();
				try {
					for (const auto& kv : other.object_value) {
						auto& ref = object_value[kv.first];
						ref = new JsonValue(*kv.second);
					}
				} catch (...) {
					for (auto& kv : object_value) {
						delete kv.second;
					}
					using ObjectType = std::unordered_map<std::string, JsonValue*>;
					object_value.~ObjectType();
					throw;
				}
				break;
			}
			case JsonValueType::Null: break;
		}
		type = other.type;
	}

	JsonValue(JsonValue&& other) noexcept : type(JsonValueType::Null) {
		switch (other.type) {
			case JsonValueType::Boolean: new (&boolean_value) bool(other.boolean_value); break;
			case JsonValueType::Number: new (&number_value) double(other.number_value); break;
			case JsonValueType::String: new (&string_value) std::string(std::move(other.string_value)); break;
			case JsonValueType::Array: new (&array_value) std::vector<JsonValue>(std::move(other.array_value)); break;
			case JsonValueType::Object: new (&object_value) std::unordered_map<std::string, JsonValue*>(std::move(other.object_value)); break;
			case JsonValueType::Null: break;
		}
		type = other.type;
		other.Clear();
	}

	JsonValue& operator=(JsonValue other) {
		Swap(other);
		return *this;
	}

	void Swap(JsonValue& other) noexcept {
		if (type == other.type) {
			switch (type) {
				case JsonValueType::Boolean: std::swap(boolean_value, other.boolean_value); break;
				case JsonValueType::Number: std::swap(number_value, other.number_value); break;
				case JsonValueType::String: std::swap(string_value, other.string_value); break;
				case JsonValueType::Array: std::swap(array_value, other.array_value); break;
				case JsonValueType::Object: std::swap(object_value, other.object_value); break;
				case JsonValueType::Null: break;
			}
		} else {
			JsonValue temp(std::move(other));
			other.~JsonValue();
			new (&other) JsonValue(std::move(*this));
			this->~JsonValue();
			new (this) JsonValue(std::move(temp));
		}
	}

	void Clear() {
		switch (type) {
			case JsonValueType::String: { using StringType = std::string; string_value.~StringType(); break; }
			case JsonValueType::Array: { using ArrayType = std::vector<JsonValue>; array_value.~ArrayType(); break; }
			case JsonValueType::Object: {
				for (auto& kv : object_value) { delete kv.second; }
				using ObjectType = std::unordered_map<std::string, JsonValue*>;
				object_value.~ObjectType();
				break;
			}
			default: break;
		}
		type = JsonValueType::Null;
	}

	std::string ToString() const{
		return ToString(false, 0);
	}
	std::string ToString(bool pretty, int indent = 0) const{
		if (pretty && (indent < 0 || indent > 100000)) {
			throw std::invalid_argument("Invalid indentation level");
		}
		switch (type)
		{
			case JsonValueType::Null:
				return "null";
			case JsonValueType::Boolean:
				return boolean_value ? "true":"false";
			case JsonValueType::Number:
				return std::to_string(number_value);
			case JsonValueType::String:
				return "\"" + EscapeString(string_value) + "\"";
			case JsonValueType::Array:
				return ArrayToString(array_value, pretty, indent);
			case JsonValueType::Object:
				return ObjectToString(object_value, pretty, indent);
		}
		return "";
	}


	void SetBoolean(bool value) {
		Clear();
		new (&boolean_value) bool(value);
		type = JsonValueType::Boolean;
	}
	bool GetBoolean() const { return boolean_value; }

	void SetNumber(double value) {
		Clear();
		new (&number_value) double(value);
		type = JsonValueType::Number;
	}
	double GetNumber() const { return number_value; }

	void SetString(const std::string& value) {
		Clear();
		new (&string_value) std::string(value);
		type = JsonValueType::String;
	}
	const std::string& GetString() const { return string_value; }
	std::string& GetString() { return string_value; }

	void SetArray() {
		Clear();
		new (&array_value) std::vector<JsonValue>();
		type = JsonValueType::Array;
	}
	bool IsArray() const { return type == JsonValueType::Array; }
	std::vector<JsonValue>& GetArray() { return array_value; }
	const std::vector<JsonValue>& GetArray() const { return array_value; }

	void SetObject() {
		Clear();
		new (&object_value) std::unordered_map<std::string, JsonValue*>();
		type = JsonValueType::Object;
	}
	bool IsObject() const { return type == JsonValueType::Object; }
	std::unordered_map<std::string, JsonValue*> &GetObJect() { return object_value; }
	const std::unordered_map<std::string, JsonValue*> &GetObject() const { return object_value; }
	void InsertIntoObject(const std::string& key , JsonValue* value){
		if (type != JsonValueType::Object){
			throw JsonParseException("Cannot insert into a non-object value.");
		}
		std::unique_ptr<JsonValue> new_value(value);
		auto result = object_value.emplace(key, new_value.get());
		if (result.second)
		{
			new_value.release();
		}
		else
		{
			delete result.first->second;
			result.first->second = new_value.release();
		}
	}


 
	private:
	
	std::string ArrayToString(const std::vector<JsonValue>& array, bool pretty, int indent) const {
		if (array.empty()) return "[]";
		std::string result = "[";
		if (pretty) result += "\n";
		for(size_t i=0; i < array.size(); i++)
		{
			if(i >0){
				result += ",";
				if (pretty) result += "\n";
				else result += " ";
			}
			if (pretty) {
				int spaces = (indent + 1) * 2;
				if (spaces > 0) result += std::string(spaces, ' ');
			}
			result += array[i].ToString(pretty, pretty ? indent + 1 : 0);
		}
		if (pretty) {
			result += "\n";
			int spaces = indent * 2;
			if (spaces > 0) result += std::string(spaces, ' ');
		}
		result +="]";
		return result;
	}
	
	std::string ObjectToString(const std::unordered_map<std::string, JsonValue*>& object, bool pretty, int indent) const{
		if (object.empty()) return "{}";
		std::string result ="{";
		if (pretty) result += "\n";
		bool first = true;
		for(const auto& kv: object)
		{
			if(!first){
				result += ",";
				if (pretty) result += "\n";
				else result += " ";
			}
			
			first =false;
			if (pretty) {
				int spaces = (indent + 1) * 2;
				if (spaces > 0) result += std::string(spaces, ' ');
			}
			result +="\""+ EscapeString(kv.first) + "\":";
			result += " "; // Single space unconditionally, handles both pretty and minified
			result += kv.second->ToString(pretty, pretty ? indent + 1 : 0);
		}
		if (pretty) {
			result += "\n";
			int spaces = indent * 2;
			if (spaces > 0) result += std::string(spaces, ' ');
		}
		result +="}";
		return result;
	}

	static std::string EscapeString(const std::string& str) {
		std::string result;
		for (char c : str) {
			switch (c) {
				case '\"': result += "\\\""; break;
				case '\\': result += "\\\\"; break;
				case '\b': result += "\\b"; break;
				case '\f': result += "\\f"; break;
				case '\n': result += "\\n"; break;
				case '\r': result += "\\r"; break;
				case '\t': result += "\\t"; break;
				default:
					if (static_cast<unsigned char>(c) < 0x20) {
						char buf[7];
						std::snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
						result += buf;
					} else {
						result += c;
					}
					break;
			}
		}
		return result;
	}
};

class JsonParser{
	public:
		static JsonValue Parse(const std::string& json_string);
	private:
		static JsonValue ParseValue(const std::string& json_string, size_t& index);
		static std::string ParseString(const std::string& json_string, size_t& index);
		static double ParseNumber(const std::string& json_string, size_t& index);
		static std::vector<JsonValue> ParseArray(const std::string& json_string, size_t& index);
		static std::unordered_map<std::string, JsonValue*> ParseObject(const std::string& json_string, size_t& index);
		static bool ParseBoolean(const std::string& json_string, size_t& index);
		static void ParseNull(const std::string& json_string, size_t& index);
		static void SkipWhitespace(const std::string& json_string, size_t& index);
		static void ExpectString(const std::string& json_string, size_t& index, const std::string& expected_string);
		[[noreturn]] static void ThrowError(const std::string& message, const std::string& json_string, size_t index);
		static void ExpectChar(const std::string& json_string, size_t& index, char expected_char);
		static std::string UnicodeCodePointToUtf8(int code_point);
		static bool IsDigit(char c);
		static void SkipComment(const std::string& json_string, size_t& index);
};
#endif
