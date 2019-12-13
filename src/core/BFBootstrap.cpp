#include "BFBootstrap.h"
#include "BFApplication.h"
#include "BFMainContext.h"

namespace BlackFox
{
	int BFBootstrap::run() const
	{
		try
		{
			//Create DI Container
			auto container = std::make_shared<cinject::Container>();
			container->bind<cinject::Container>().toConstant(container);

			//Create main context
			auto mainContext = makeContext<BFMainContext>(container, true);

			//Execute the app
			auto app = container->get<BFApplication>();
			return app->execute();
		}
		catch(const std::exception& err)
		{
			BF_ERROR("{}", err.what())
			return EXIT_FAILURE;
		}
	}
}
