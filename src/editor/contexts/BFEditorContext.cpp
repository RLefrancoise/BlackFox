#include "BFEditorContext.h"

#include "BFCommandInstaller.h"
#include "BFCoreInstaller.h"
#include "BFWindowInstaller.h"

using namespace BlackFox::Editor;

BFEditorContext::BFEditorContext(DiContainer container)
: BFBaseContext(std::move(container))
{
}

void BFEditorContext::init()
{
	addInstaller(std::make_shared<BFCommandInstaller>(m_container));
	addInstaller(std::make_shared<BFCoreInstaller>(m_container));
	addInstaller(std::make_shared<BFWindowInstaller>(m_container));
}
