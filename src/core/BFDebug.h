#ifndef BLACKFOX_DEBUG_H
#define BLACKFOX_DEBUG_H

#ifdef _DEBUG
#	include <fmt/format.h>
#	define BF_DEBUG_HEADER (fmt::format("{}:{} - {} - ", __FILE__, __LINE__, __FUNCTION__))
#	define BF_PRINT(x, ...) fmt::print(BF_DEBUG_HEADER + (x), __VA_ARGS__);
#	define BF_EXCEPTION(x, ...) throw std::runtime_error(BF_DEBUG_HEADER + fmt::format((x), __VA_ARGS__));
#else
#	define BF_PRINT(x, ...)
#	define BF_EXCEPTION(x, ...)
#endif

#endif