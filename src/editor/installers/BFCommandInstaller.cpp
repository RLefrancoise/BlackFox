#include "BFCommandInstaller.h"


#include "BFCreateProjectCommand.h"
#include "BFLoadProjectCommand.h"
#include "BFQuitEditorCommand.h"
#include "BFSelectSceneCommand.h"

namespace BlackFox::Editor
{
	BFCommandInstaller::BFCommandInstaller(DiContainer container)
		: BFBaseInstaller(std::move(container))
	{
	}

	void BFCommandInstaller::installBindings()
	{
		m_container->bind<BFCreateProjectCommand>().toSelf();
		m_container->bind<BFLoadProjectCommand>().toSelf();
		m_container->bind<BFQuitEditorCommand>().toSelf();
		m_container->bind<BFSelectSceneCommand>().toSelf();
	}
}
