#include "core/BFApplication.h"
#include <cinject/cinject.h>
#include "core/BFQuitApplicationCommand.h"

using namespace BlackFox;
using namespace cinject;

int main(int argc, char** argv)
{
	try
	{
		auto container = std::make_shared<Container>();

		container->bind<Container>().toConstant(container);
		container->bind<BFCommandManager>().toSelf().inSingletonScope();
		container->bind<BFApplication>().toSelf().inSingletonScope();

		container->bind<BFQuitApplicationCommand>().toSelf();

		//Execute the app
		auto app = container->get<BFApplication>();
		return app->execute();
	} catch(const std::exception& err)
	{
		BF_ERROR("{}", err.what())
		return EXIT_FAILURE;
	}	
}