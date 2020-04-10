#pragma once
#include "BFBaseInstaller.h"

namespace BlackFox::Editor
{
	class BFCommandInstaller final : public BFBaseInstaller
	{
	public:
		explicit BFCommandInstaller(DiContainer container);
		void installBindings() override;
	};
}
