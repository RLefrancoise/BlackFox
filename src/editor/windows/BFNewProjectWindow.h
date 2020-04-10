#pragma once

#include <cinject/cinject.h>
#include "BFWindow.h"

namespace BlackFox::Editor
{
	class BFNewProjectWindow final: public BFWindow<BFNewProjectWindow>
	{
	public:
		CINJECT(BFNewProjectWindow());
		[[nodiscard]] BFNewProjectWindow* clone() const override;

	protected:
		void drawContent() override;

	private:
		std::string m_projectName;
	};
}