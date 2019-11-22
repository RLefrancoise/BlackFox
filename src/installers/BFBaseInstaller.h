#ifndef BLACKFOX_BASEINSTALLER_H
#define BLACKFOX_BASEINSTALLER_H

#include "IBFInstaller.h"
#include "../BFTypeDefs.h"

namespace BlackFox
{
	class BFBaseInstaller : public IBFInstaller
	{
	public:
		explicit BFBaseInstaller(DiContainer container);

	protected:
		DiContainer m_container;
	};
}

#endif