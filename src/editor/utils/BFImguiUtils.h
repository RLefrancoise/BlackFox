#pragma once

#include <regex>
#include "imgui.h"

namespace BlackFox::Editor
{
	namespace Callbacks
	{
		namespace CharFilters
		{
			/// Alpha numeric filter
			static auto alphaNumeric = [](ImGuiInputTextCallbackData* data) -> int
			{
				const wchar_t str[2] = { data->EventChar, '\0' };

				if(!std::regex_match(str, std::wregex(L"[A-Za-z0-9_\\-\\s]")))
				{
					return 1;
				}

				return 0;
			};
		}
	}
}
