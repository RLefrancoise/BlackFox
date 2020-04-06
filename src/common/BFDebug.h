#pragma once

#include <iostream>
#include <fmt/format.h>
#include <termcolor/termcolor.hpp>

namespace BlackFox
{
	template<typename FormatType, typename ...Args>
	static constexpr std::string format(FormatType str, Args... args)
	{
		return fmt::format("{}:{} - {} - {}", __FILE__, __LINE__, __FUNCTION__, fmt::format(static_cast<std::string>(str), args...));
	}

	template<typename FormatType, typename ...Args>
	static constexpr void print(FormatType str, Args... args)
	{
#if defined(BF_DEBUG) || defined(_DEBUG)
		std::cout << format(str, args...) << std::endl;
#endif
	}

	template<typename FormatType, typename ...Args>
	static constexpr void warning(FormatType str, Args... args)
	{
		std::cout << termcolor::yellow << format(str, args...) << termcolor::reset << std::endl;
	}

	template<typename FormatType, typename ...Args>
	static constexpr void error(FormatType str, Args... args)
	{
		std::cout << termcolor::red << format(str, args...) << termcolor::reset << std::endl;
		std::cerr << BlackFox::format(str, args...) << std::endl;
	}

	template<typename FormatType, typename ...Args>
	static constexpr void exception(FormatType str, Args... args)
	{
		throw std::runtime_error(format(str, args...));
	}
}