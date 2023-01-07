#pragma once
#ifndef _JSON_
#define _JSON_
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <cmath>
enum class JsonValueType{
	Null,
	Boolean,
	Number,
	String,
	Array,
	Object
};


struct JsonValue{

	JsonValue(JsonValueType type_ = JsonValueType::Null) : type(type_){}
	JsonValueType type;
	bool boolean_value;
	double number_value;
	std::string string_value;
	std::vector<JsonValue> array_value;
	std::unordered_map<std::string, JsonValue* > object_value;
	std::string ToString() const{
		switch (type)
		{
			case JsonValueType::Null:
				return "null";
			case JsonValueType::Boolean:
				return boolean_value ? "true":"false";
			case JsonValueType::Number:
				return std::to_string(number_value);
			case JsonValueType::String:
				return "\"" +string_value +"\"";
			case JsonValueType::Array:
				return ArrayToString(array_value);
			case JsonValueType::Object:
				return ObjectToString(object_value);
		}
	}
	
	private:
	
	std::string ArrayToString(const std::vector<JsonValue>& array) const {
		std::string result = "[";
		for(size_t i=0; i < array.size(); i++)
		{
			if(i >0){
				result += ", ";
			}
			result += array[i].ToString();
		}
		result +="]";
		return result;
	}
	
	std::string ObjectToString(const std::unordered_map<std::string, JsonValue*>& object) const{
		std::string result ="{";
		bool first = true;
		for(const auto& kv: object)
		{
			if(!first){
				result += ", ";
			}
			
			first =false;
			result +="\""+ kv.first + "\": " + kv.second->ToString();
		}
		result +="}";
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
		static void ExpectChar(const std::string& json_string, size_t& index, char expected_char);
		static std::string UnicodeCodePointToUtf8(int code_point);
		static bool IsDigit(char c);
};
#endif
