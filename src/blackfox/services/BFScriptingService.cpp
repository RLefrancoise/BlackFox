#include "BFScriptingService.h"
#include "BFApplication.h"
#include "BFScriptingManager.h"
#include "BFDebug.h"

namespace BlackFox
{
    BFScriptingService::BFScriptingService(
        BFApplication::Ptr application,
        std::shared_ptr<BFScriptingManager> scriptingManager)
        : IBFApplicationService(std::move(application))
        , m_scriptingManager(std::move(scriptingManager))
        {}

    void BFScriptingService::run()
    {
        BF_PRINT("Run scripting service");
        m_scriptingManager->registerEntities();
    }
}