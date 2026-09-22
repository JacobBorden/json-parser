#pragma once
#ifndef _JSON_ERROR_
#define _JSON_ERROR_
#include <exception>
#include <string>

class JsonParseException : public std::exception
{
	public:
		JsonParseException(const std::string& message, size_t line = 0, size_t column = 0)
			: message_(message), line_(line), column_(column) {
			if (line > 0) {
				message_ += " at line " + std::to_string(line) + ", column " + std::to_string(column);
			}
		}
		const char* what() const noexcept override { return message_.c_str(); }
		size_t GetLine() const { return line_; }
		size_t GetColumn() const { return column_; }
	private:
		std::string message_;
		size_t line_;
		size_t column_;
};

#endif
