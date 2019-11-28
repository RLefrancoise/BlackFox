#include "BFBaseContext.h"

namespace BlackFox
{
	BFBaseContext::BFBaseContext(DiContainer container) :
	m_init(false),
	m_container(std::move(container))
	{
	}

	void BFBaseContext::run()
	{
		if(!m_init)
		{
			init();
			m_init = true;
		}

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