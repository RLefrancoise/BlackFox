#pragma once

#include <filesystem>

namespace BlackFox::Editor::Events
{
	namespace DataBrowser
	{
		/*!
		 * \brief	Event sent when a file is selected by the data browser
		 */
		struct BFFileSelectedEvent
		{
			std::filesystem::path file;
		};
	}
	
}