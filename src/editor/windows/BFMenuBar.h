#pragma once

#include <memory>

#include "BFCommandManager.h"
#include "IBFWindow.h"

namespace BlackFox::Editor
{
	class BFWindowManager;
	
	class BFMenuBar final : public IBFWindow
	{
	public:
		typedef std::shared_ptr<BFMenuBar> Ptr;

		CINJECT(BFMenuBar(
			BFCommandManager::Ptr commandManager,
			std::shared_ptr<BFWindowManager> windowManager));
		bool draw() override;
		[[nodiscard]] BFMenuBar* clone() const override;

	private:

		void fileMenu() const;
		void windowMenu() const;
		
		BFCommandManager::Ptr m_commandManager;
		std::shared_ptr<BFWindowManager> m_windowManager;
	};
}
