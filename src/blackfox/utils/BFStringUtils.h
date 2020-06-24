#pragma once

#include <functional>
#include <string>
#include <vector>
#include <numeric>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox::Utils
{
	/*!
	 *	Default stringify function for join function. It uses std::to_string.
	 */
	template<typename T>
	static std::function<std::string(const T&)> defaultStringify = [](const T& t) -> std::string {
		if constexpr(std::is_same_v<T, std::string>) return t;
		return std::to_string(t);
	};

	/*!
	 * \brief				Join values of the specified vector in a string with the specified delimiter.
	 *
	 * \param	v			Values to join
	 * \param	delimiter	String to separate each value
	 * \param	stringify	Function to use to stringify each value
	 */
	template <typename T>
	static std::string join(const std::vector<T>& v, const std::string& delimiter = ",", std::function<std::string(const T&)> stringify = defaultStringify<T>)
	{
		std::string str;
		if (!v.empty())
		{
			str = std::accumulate(v.begin() + 1, v.end(), stringify(v[0]), [delimiter, stringify](const std::string& a, const T& b) {
				return a + delimiter + stringify(b);
			});
		}

		return str;
	}
}