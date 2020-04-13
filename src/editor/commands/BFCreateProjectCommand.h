#pragma once

#include "IBFCommand.h"
#include <filesystem>

namespace BlackFox::Editor
{
	class BFCreateProjectCommand final: public BFCommandBase<BFCreateProjectCommand>
	{
	public:
		void execute(const std::filesystem::path& projectFolder);
		[[nodiscard]] BFCreateProjectCommand* clone() const override;
	};
}
