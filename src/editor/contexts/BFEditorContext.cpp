#include "BFEditorContext.h"
#include "BFCoreInstaller.h"

using namespace BlackFox::Editor;

BFEditorContext::BFEditorContext(DiContainer container)
: BFBaseContext(std::move(container))
{
}

void BFEditorContext::init()
{
	addInstaller(std::make_shared<BFCoreInstaller>(m_container));
}
