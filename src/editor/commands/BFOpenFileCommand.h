#pragma once
#include "IBFCommand.h"
#include <filesystem>

#include "BFWindowManager.h"

namespace BlackFox::Editor
{
	class BFOpenFileCommand final : public BFCommandBase<BFOpenFileCommand>
	{
	public:
		CINJECT(BFOpenFileCommand(BFWindowManager::Ptr windowManager));
		
		[[nodiscard]] BFOpenFileCommand* clone() const override;
		void execute(const std::filesystem::path& file);
		void undo() override;
		void redo() override;

	private:
		BFWindowManager::Ptr m_windowManager;
	};
}
