#include "BFBootstrap.h"
#include "BFApplication.h"
#include "BFMainContext.h"

#include <rttr/library.h>

namespace BlackFox
{
	int BFBootstrap::run() const
	{
		try
		{
			//Load blackfox dll
			rttr::library lib("blackfox");
			if(!lib.load())
			{
				exception("Failed to load blackfox library: {}", lib.get_error_string().to_string());
			}
			
			//Create DI Container
			auto container = std::make_shared<cinject::Container>();
			container->bind<cinject::Container>().toConstant(container);

			//Create main context
			auto mainContext = makeContext<BFMainContext>(container, true);

			//Execute the app
			const auto app = container->get<BFApplication>();
			return app->execute();
		}
		catch(const std::exception& err)
		{
			error("{}", err.what());
			return EXIT_FAILURE;
		}
	}
}
