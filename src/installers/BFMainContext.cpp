#include "BFMainContext.h"
#include "BFCoreInstaller.h"
#include "BFEntitiesInstaller.h"
#include "BFDataInstaller.h"
#include "BFScriptingInstaller.h"

namespace BlackFox
{
	BFMainContext::BFMainContext(DiContainer container)
	: BFBaseContext(std::move(container))
	{
	}

	void BFMainContext::init()
	{
		addInstaller(std::make_shared<BFCoreInstaller>(m_container));
		addInstaller(std::make_shared<BFEntitiesInstaller>(m_container));
		addInstaller(std::make_shared<BFDataInstaller>(m_container));
		addInstaller(std::make_shared<BFScriptingInstaller>(m_container));
	}
}
