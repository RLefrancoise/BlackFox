#ifndef BLACKFOX_COREINSTALLER_H
#define BLACKFOX_COREINSTALLER_H

#include "BFBaseInstaller.h"

namespace BlackFox
{
	class BFCoreInstaller : public BFBaseInstaller
	{
	public:
		explicit BFCoreInstaller(DiContainer container);
		void installBindings() override;
	};
}

#endif