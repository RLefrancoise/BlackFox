#include "BFServicesInstaller.h"

#include "BFScriptingService.h"
#include "BFCreateDefaultWorldService.h"
#include "BFApplication.h"
#include "BFScriptingManager.h"

namespace BlackFox
{
    BFServicesInstaller::BFServicesInstaller(DiContainer container) : BFBaseInstaller(std::move(container))
    {}

    void BFServicesInstaller::installBindings()
    {
        m_container->bind<IBFApplicationService>().to<BFScriptingService>().inSingletonScope();
        m_container->bind<IBFApplicationService>().to<BFCreateDefaultWorldService>().inSingletonScope();
    }
}