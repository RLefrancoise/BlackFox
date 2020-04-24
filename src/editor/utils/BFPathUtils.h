#pragma once
#include <filesystem>
#include <string>

namespace BlackFox::Editor::Utils
{
	std::filesystem::path skipPathUntil(const std::filesystem::path& startPath, const std::string& untilName)
	{
		for(const auto& p : startPath)
		{
			if (p != untilName) continue;
		}
	}
}
