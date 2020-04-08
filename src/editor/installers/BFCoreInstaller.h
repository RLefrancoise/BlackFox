#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox::Editor
{
	class BFCoreInstaller final : public BFBaseInstaller
	{
	public:
		explicit BFCoreInstaller(DiContainer container);
		void installBindings() override;
	};
}
