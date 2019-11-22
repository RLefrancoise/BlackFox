#ifndef BLACKFOX_DEBUG_H
#define BLACKFOX_DEBUG_H

#include <iostream>
#include <fmt/format.h>
#include <termcolor/termcolor.hpp>

#define BF_DEBUG_HEADER (fmt::format("{}:{} - {} - ", __FILE__, __LINE__, __FUNCTION__))

#ifdef _DEBUG
//Print
#	define BF_PRINT(x, ...)		std::cout << fmt::format(BF_DEBUG_HEADER + (x), __VA_ARGS__) << std::endl;
//Warning
#	define BF_WARNING(x, ...)	std::cout << termcolor::yellow << fmt::format(BF_DEBUG_HEADER + (x), __VA_ARGS__) << termcolor::reset << std::endl;
//Error
#	define BF_ERROR(x, ...)		std::cout << termcolor::red << fmt::format(BF_DEBUG_HEADER + (x), __VA_ARGS__) << termcolor::reset << std::endl; \
								std::cerr << fmt::format(BF_DEBUG_HEADER + (x), __VA_ARGS__) << std::endl;
#else
#	define BF_PRINT(x, ...)
#	define BF_WARNING(x, ...)
#	define BF_ERROR(x, ...)
#endif

//Exception
#define BF_EXCEPTION(x, ...)	throw std::runtime_error(BF_DEBUG_HEADER + fmt::format((x), __VA_ARGS__));

#endif