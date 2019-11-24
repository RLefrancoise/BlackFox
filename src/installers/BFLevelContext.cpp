#include "BFLevelContext.h"
#include "BFLevelInstaller.h"

namespace BlackFox
{
	BFLevelContext::BFLevelContext(DiContainer container, BFLevel::Ptr level) : BFBaseContext(container), m_level(level)
	{
	}

	void BFLevelContext::init()
	{
		addInstaller(std::make_shared<BFLevelInstaller>(m_container, m_level));
	}
}
