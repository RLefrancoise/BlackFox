#pragma once

#include "IBFApplicationService.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
    class BFScriptingManager;

    class BFScriptingService final : public IBFApplicationService
    {
    public:
        CINJECT(BFScriptingService(std::shared_ptr<BFApplication> application, std::shared_ptr<BFScriptingManager> scriptingManager));
        void run() override;

    private:
        std::shared_ptr<BFScriptingManager> m_scriptingManager;
    };
}