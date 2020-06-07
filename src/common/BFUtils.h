#ifndef BLACKFOX_UTILS_H
#define BLACKFOX_UTILS_H

#include <vector>
#include <tuple>

namespace BlackFox
{
	static constexpr bool hasFlag(const unsigned int mask, const unsigned int flag)
	{
		return (mask & flag) == flag;
	}

	template <typename T, std::size_t... Indices>
	static constexpr auto vectorToTupleHelper(const std::vector<T>& v, std::index_sequence<Indices...>) {
		return std::make_tuple(v[Indices]...);
	}

	template <std::size_t N, typename T>
	static constexpr auto vectorToTuple(const std::vector<T>& v) {
		assert(v.size() == N);
		return vectorToTupleHelper(v, std::make_index_sequence<N>());
	}
}

#endif