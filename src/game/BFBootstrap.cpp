#include "BFBootstrap.h"
#include "BFApplication.h"
#include "BFMainContext.h"
#include "BFDebug.h"
#include "BFScriptingManager.h"

#include <rttr/library.h>

namespace BlackFox
{
	int BFBootstrap::run() const
	{
		try
		{
#ifdef BLACKFOX_SHARED_LIB
			//Load blackfox dll
			rttr::library lib("blackfox");
			if(!lib.load())
			{
				BF_EXCEPTION("Failed to load blackfox library: {}", lib.get_error_string().to_string());
			}
#endif
			
			//Create DI Container
			auto container = std::make_shared<cinject::Container>();
			container->bind<cinject::Container>().toConstant(container);

			//Create main context
			auto mainContext = makeContext<BFMainContext>(container, true);

			//Execute the app
			const auto app = container->get<BFApplication>();
			if(!app->init())
			{
				BF_EXCEPTION("Failed to init application");
			}

			//Launch test script
			const auto scriptManager = container->get<BFScriptingManager>();
			BF_PRINT("Test.lua result: {}", scriptManager->evalFile<bool>("data/test.lua"));

			return app->execute();
		}
		catch(const std::exception& err)
		{
			BF_ERROR("{}", err.what());
			return EXIT_FAILURE;
		}
	}
}
