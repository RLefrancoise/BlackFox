#include "BFMainContext.h"
#include "BFCoreInstaller.h"
#include "BFEntitiesInstaller.h"

namespace BlackFox
{
	BFMainContext::BFMainContext(DiContainer container) : BFBaseContext(container)
	{
	}

	void BFMainContext::init()
	{
		addInstaller(std::make_shared<BFCoreInstaller>(m_container));
		addInstaller(std::make_shared<BFEntitiesInstaller>(m_container));
	}
}
