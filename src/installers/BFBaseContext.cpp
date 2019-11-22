#include "BFBaseContext.h"

namespace BlackFox
{
	BFBaseContext::BFBaseContext(DiContainer container) : m_container(container)
	{
	}

	void BFBaseContext::run()
	{
		for (auto& installer : m_installers)
		{
			installer->installBindings();
		}
	}

	void BFBaseContext::addInstaller(DiInstaller installer)
	{
		m_installers.emplace_back(installer);
	}
}