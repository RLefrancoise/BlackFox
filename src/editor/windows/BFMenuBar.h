#pragma once

#include <memory>

#include "BFCommandManager.h"
#include "IBFWindow.h"

namespace BlackFox::Editor
{
	class BFMenuBar final : public IBFWindow
	{
	public:
		typedef std::shared_ptr<BFMenuBar> Ptr;

		CINJECT(BFMenuBar(BFCommandManager::Ptr commandManager));
		void draw() override;
		[[nodiscard]] BFMenuBar* clone() const override;

	private:
		BFCommandManager::Ptr m_commandManager;
	};
}
