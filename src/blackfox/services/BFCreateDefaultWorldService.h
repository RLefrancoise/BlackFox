#pragma once

#include "IBFApplicationService.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
    class BFCreateDefaultWorldService final: public IBFApplicationService
    {
    public:
        CINJECT(BFCreateDefaultWorldService(std::shared_ptr<BFApplication> application, DiContainer container));
        void run() override;

    private:
        DiContainer m_container;
    };
}