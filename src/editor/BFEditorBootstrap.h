#pragma once

namespace BlackFox::Editor
{
	class BFEditorBootstrap
	{
	public:
		constexpr BFEditorBootstrap() = default;
		~BFEditorBootstrap() = default;
		constexpr BFEditorBootstrap(BFEditorBootstrap&& bootstrap) noexcept = default;
		constexpr BFEditorBootstrap& operator=(BFEditorBootstrap&& bootstrap) = default;

		constexpr BFEditorBootstrap(const BFEditorBootstrap& app) = delete;
		constexpr BFEditorBootstrap& operator=(const BFEditorBootstrap& app) = delete;

		[[nodiscard]] int run(int argc, char** argv) const;
	};
}