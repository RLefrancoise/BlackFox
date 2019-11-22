#include <cinject/cinject.h>

#include "core/BFApplication.h"
#include "installers/BFMainContext.h"

using namespace BlackFox;
using namespace cinject;

int main(int argc, char** argv)
{
	try
	{
		//Create DI Container
		auto container = std::make_shared<Container>();
		container->bind<Container>().toConstant(container);
		
		//Create main context
		auto mainContext = makeContext<BFMainContext>(container);

		//Execute the app
		auto app = container->get<BFApplication>();
		return app->execute();
	} catch(const std::exception& err)
	{
		BF_ERROR("{}", err.what())
		return EXIT_FAILURE;
	}	
}