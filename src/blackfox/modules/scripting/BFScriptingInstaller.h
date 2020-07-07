#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox
{
	class BLACKFOX_EXPORT BFScriptingInstaller final : public BFBaseInstaller
	{
	public:
		explicit BFScriptingInstaller(DiContainer container);
		void installBindings() override;
	};
}