#pragma once

#include "IBFCommand.h"

namespace BlackFox::Editor
{
	class BFSelectSceneCommand final: public BFCommandBase<BFSelectSceneCommand>
	{
	public:
		void execute(int scene);
		[[nodiscard]] BFSelectSceneCommand* clone() const override;
	};
}
