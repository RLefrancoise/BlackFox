#include "BFEditorContext.h"
#include "BFCoreInstaller.h"
#include "installers/BFWindowInstaller.h"

using namespace BlackFox::Editor;

BFEditorContext::BFEditorContext(DiContainer container)
: BFBaseContext(std::move(container))
{
}

void BFEditorContext::init()
{
	addInstaller(std::make_shared<BFCoreInstaller>(m_container));
	addInstaller(std::make_shared<BFWindowInstaller>(m_container));
}
