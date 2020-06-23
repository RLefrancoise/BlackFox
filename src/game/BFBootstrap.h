#pragma once

namespace BlackFox
{
	class BFBootstrap
	{
	public:
		constexpr BFBootstrap() = default;
		~BFBootstrap() = default;
		constexpr BFBootstrap(BFBootstrap&& bootstrap) noexcept = default;
		constexpr BFBootstrap& operator=(BFBootstrap&& bootstrap) = default;
		
		constexpr BFBootstrap(const BFBootstrap& app) = delete;
		constexpr BFBootstrap& operator=(const BFBootstrap& app) = delete;

		[[nodiscard]] int run(int argc, char** argv) const;
	};
}
