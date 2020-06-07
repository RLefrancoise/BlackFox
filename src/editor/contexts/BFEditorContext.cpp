#include "BFEditorContext.h"

#include "BFCommandInstaller.h"
#include "BFCoreInstaller.h"
#include "BFDataInstaller.h"
#include "BFWindowInstaller.h"

namespace BlackFox::Editor
{
	BFEditorContext::BFEditorContext(BlackFox::DiContainer container)
	: BFBaseContext(std::move(container))
	{
	}

	void BFEditorContext::init()
	{
		addInstaller(std::make_shared<BFCommandInstaller>(m_container));
		addInstaller(std::make_shared<BFCoreInstaller>(m_container));
		addInstaller(std::make_shared<BFDataInstaller>(m_container));
		addInstaller(std::make_shared<BFWindowInstaller>(m_container));
	}
}