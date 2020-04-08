#pragma once
#include "BFBaseInstaller.h"

namespace BlackFox::Editor
{
	class BFWindowInstaller final : public BFBaseInstaller
	{
	public:
		explicit BFWindowInstaller(DiContainer container);
		void installBindings() override;
	};
}
