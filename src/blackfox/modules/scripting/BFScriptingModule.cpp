#include "BFScriptingModule.h"

#include "BFScriptingInstaller.h"
#include "BFDebug.h"
#include "BFScriptingManager.h"


namespace BlackFox::Scripting
{
    BFScriptingModule::BFScriptingModule(DiContainer container)
    : BFApplicationModule(std::move(container))
    {}

    void BFScriptingModule::install(const DiContext &context)
    {
        context->addInstaller(std::make_shared<BFScriptingInstaller>(m_container));
    }

    void BFScriptingModule::onInit()
    {
        BFApplicationModule::onInit();

        BF_PRINT("Run scripting module");

        auto scriptingManager = m_container->get<BFScriptingManager>();
        scriptingManager->registerEntities();
    }
}