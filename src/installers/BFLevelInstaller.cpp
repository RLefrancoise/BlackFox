#include "BFLevelInstaller.h"
#include "../core/BFLevel.h"

namespace BlackFox
{
	BFLevelInstaller::BFLevelInstaller(DiContainer container, BFLevel::Ptr level) : BFBaseInstaller(container), m_level(level)
	{
	}

	void BFLevelInstaller::installBindings()
	{
		m_container->bind<BFLevel>().toConstant(m_level);
	}
}
