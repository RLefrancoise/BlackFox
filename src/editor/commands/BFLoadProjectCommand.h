#pragma once

#include "IBFCommand.h"
#include <filesystem>

namespace BlackFox::Editor
{
	class BFLoadProjectCommand final: public BFCommandBase<BFLoadProjectCommand>
	{
	public:
		BFLoadProjectCommand();

		void execute(const std::filesystem::path& projectPath);
		
		[[nodiscard]] BFLoadProjectCommand* clone() const override;
		void undo() override {}
		void redo() override {}
	};
}
