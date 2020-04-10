#pragma once

#include "BFCommand.h"

namespace BlackFox::Editor
{
	class BFSelectSceneCommand final: public BFCommand
	{
	public:
		BFSelectSceneCommand();
		void setScene(int scene);
		void execute() override;
		[[nodiscard]] BFSelectSceneCommand* clone() const override;

	private:
		int m_scene;
	};
}
