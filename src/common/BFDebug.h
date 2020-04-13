#pragma once

#include <iostream>
#include <fmt/format.h>
#include <termcolor/termcolor.hpp>

namespace BlackFox
{
	template<typename FormatType, typename ...Args>
	static constexpr std::string format(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		return fmt::format("{}:{} - {} - {}", file, line, function, fmt::format(static_cast<std::string>(str), args...));
	}

	template<typename FormatType, typename ...Args>
	static constexpr void print(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
#if defined(BF_DEBUG) || defined(_DEBUG)
		std::cout << format(file, line, function, str, args...) << std::endl;
#endif
	}

	template<typename FormatType, typename ...Args>
	static constexpr void warning(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		std::cout << termcolor::yellow << format(file, line, function, str, args...) << termcolor::reset << std::endl;
	}

	template<typename FormatType, typename ...Args>
	static constexpr void error(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		const auto fmt = format(file, line, function, str, args...);
		std::cout << termcolor::red << fmt << termcolor::reset << std::endl;
		std::cerr << fmt << std::endl;
	}

	template<typename FormatType, typename ...Args>
	static constexpr void exception(const char* file, const int line, const char* function, FormatType str, Args... args)
	{
		throw std::runtime_error(format(file, line, function, str, args...));
	}
}

#define BF_PRINT(fmt, ...)		BlackFox::print(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__##);
#define BF_WARNING(fmt, ...)	BlackFox::warning(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__##);
#define BF_ERROR(fmt, ...)		BlackFox::error(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__##);
#define BF_EXCEPTION(fmt, ...)	BlackFox::exception(__FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__##);