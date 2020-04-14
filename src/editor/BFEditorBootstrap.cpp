#include "BFEditorBootstrap.h"

#include <cstdlib>
#include <rttr/library.h>
#include <cinject/cinject.h>

#include "BFDebug.h"
#include "BFEditorApplication.h"
#include "BFEditorContext.h"

using namespace BlackFox::Editor;

int BFEditorBootstrap::run() const
{
	try
	{
#ifdef BLACKFOX_SHARED_LIB
		//Load blackfox dll
		rttr::library lib("blackfox");
		if (!lib.load())
		{
			BF_EXCEPTION("Failed to load blackfox library: {}", lib.get_error_string().to_string());
		}
#endif

		//Create DI Container
		auto container = std::make_shared<cinject::Container>();
		container->bind<cinject::Container>().toConstant(container);

		//Create editor context
		auto editorContext = makeContext<BFEditorContext>(container, true);
		
		//Create editor app
		const auto editorApp = container->get<BFEditorApplication>();
		return editorApp->execute();
	}
	catch(const std::exception& err)
	{
		BF_ERROR("{}", err.what());
		return EXIT_FAILURE;
	}
}