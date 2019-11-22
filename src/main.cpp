#include "core/BFApplication.h"
#include <cinject/cinject.h>
#include "installers/BFMainContext.h"
#include "installers/BFCoreInstaller.h"

using namespace BlackFox;
using namespace cinject;

DiContext createMainContext(DiContainer container)
{
	DiContext mainContext = std::make_shared<BFMainContext>(container);
	mainContext->addInstaller(std::make_shared<BFCoreInstaller>(container));

	return mainContext;
}

int main(int argc, char** argv)
{
	try
	{
		//Create DI Container
		auto container = std::make_shared<Container>();
		container->bind<Container>().toConstant(container);
		
		//Create main context
		auto mainContext = createMainContext(container);
		mainContext->run();

		//Execute the app
		auto app = container->get<BFApplication>();
		return app->execute();
	} catch(const std::exception& err)
	{
		BF_ERROR("{}", err.what())
		return EXIT_FAILURE;
	}	
}