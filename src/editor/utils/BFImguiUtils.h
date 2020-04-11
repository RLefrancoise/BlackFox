#pragma once

#include "imgui.h"

namespace BlackFox::Editor
{
	namespace Callbacks
	{
		namespace CharFilters
		{
			static auto alphaNumeric = [](ImGuiInputTextCallbackData* data) -> int
			{			
				//Check alpha numeric
				if ((data->EventChar >= 'A' && data->EventChar <= 'Z') ||
					(data->EventChar >= 'a' && data->EventChar <= 'z') ||
					(data->EventChar >= '0' && data->EventChar <= '9') ||
					data->EventChar == ' ' || data->EventChar == '-' || data->EventChar == '_')
				{
					return 0;
				}

				return 1;
			};
		}
	}
}
