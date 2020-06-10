#pragma once

#include <memory>

#include "IBFCommand.h"
#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
	class BFApplication;

	class BLACKFOX_EXPORT BFQuitApplicationCommand final : public BFCommandBase<BFQuitApplicationCommand>
	{		
	private:
		std::shared_ptr<BFApplication> m_application;

	public:
		CINJECT(BFQuitApplicationCommand(std::shared_ptr<BFApplication> application));

		void execute();
		[[nodiscard]] BFQuitApplicationCommand* clone() const override;
		void undo() override {}
		void redo() override {}
	};
}