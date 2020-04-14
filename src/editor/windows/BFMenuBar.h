#pragma once

#include <memory>

#include "BFCommandManager.h"
#include "BFWindowManager.h"
#include "BFDataManager.h"

namespace BlackFox::Editor
{	
	class BFMenuBar
	{
	public:
		typedef std::shared_ptr<BFMenuBar> Ptr;

		CINJECT(BFMenuBar(
			BFCommandManager::Ptr commandManager,
			BFWindowManager::Ptr windowManager,
			BFDataManager::Ptr dataManager));
		void render() const;

	private:

		void fileMenu() const;
		void editMenu() const;
		void windowMenu() const;
		
		BFCommandManager::Ptr m_commandManager;
		BFWindowManager::Ptr m_windowManager;
		BFDataManager::Ptr m_dataManager;
	};
}
