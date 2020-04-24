#pragma once
#include "BFBaseInstaller.h"

namespace BlackFox::Editor
{
	class BFDataInstaller final: public BFBaseInstaller
	{
	public:
		CINJECT(BFDataInstaller(DiContainer container));
		void installBindings() override;
	};
}
