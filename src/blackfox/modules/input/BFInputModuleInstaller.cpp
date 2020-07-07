#include "BFInputModuleInstaller.h"
#include "BFInput.h"

namespace BlackFox::Input
{
    BFInputModuleInstaller::BFInputModuleInstaller(BlackFox::DiContainer container)
    : BFBaseInstaller(std::move(container))
    {}

    void BFInputModuleInstaller::installBindings()
    {
        //Input
        m_container->bind<BFInput>().toSelf().inSingletonScope();
    }
}