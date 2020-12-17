#pragma once

#include <functional>
#include <string>
#include <vector>
#include <numeric>
#include <filesystem>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox::Utils
{
    template<typename T>
    static BFString stringify(const T& arg)
    {
        return BFString(std::to_string(arg));
    }

    static BFString stringify(const BFString& arg)
    {
        return arg;
    }

    static BFString stringify(const std::string& arg)
    {
        return arg;
    }

	/*!
	 *	Default stringify function for join function. It uses std::to_string.
	 */
	template<typename T>
	static std::function<BFString(const T&)> defaultStringify = [](const T& t) -> BFString {
		return stringify(t);
	};

	static std::function<BFString(const std::filesystem::path&)> stringifyPath = [](const std::filesystem::path& p) -> BFString
	{
		return p.string();
	};

	/*!
	 * \brief				Join values of the specified vector in a string with the specified delimiter.
	 *
	 * \param	v			Values to join
	 * \param	delimiter	String to separate each value
	 * \param	stringify	Function to use to stringify each value
	 */
	template <typename T>
	static BFString join(const std::vector<T>& v, const BFString& delimiter = ",", std::function<BFString(const T&)> stringify = defaultStringify<T>)
	{
        BFString str;
		if (!v.empty())
		{
			str = std::accumulate(v.begin() + 1, v.end(), stringify(v[0]), [delimiter, stringify](const BFString& a, const T& b) {
				return a + delimiter + stringify(b);
			});
		}

		return str;
	}

	static BFString join(const std::vector<BFString>& v, const BFString& delimiter = ",")
	{
		return join<BFString>(v, delimiter);
	}

    static BFString join(const std::vector<std::string>& v, const BFString& delimiter = ",")
    {
        std::vector<BFString> vec;
        vec.reserve(v.size());

        for(const auto& s : v)
        {
            vec.emplace_back(s);
        }

        return join<BFString>(vec, delimiter);
    }

    /*!
     * Convert an array of elements to a BFString array
     * @tparam T    Type of the elements
     * @param v     The array
     * @return      The array of BFString
     */
    template<typename T>
    static std::vector<BFString> toBFStringArray(const std::vector<T>& v)
    {
        std::vector<BFString> arr;
        arr.reserve(v.size());

        for(const auto& t : v)
        {
            arr.emplace_back(stringify(t));
        }

        return arr;
    }
}