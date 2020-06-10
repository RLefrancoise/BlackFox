#pragma once

#include "IBFService.h"

namespace BlackFox
{
    class BFApplication;

    /*!
     * Blackfox application service
     */
    class IBFApplicationService : public IBFService
    {
    public:
        typedef std::shared_ptr<IBFApplicationService> Ptr;

        explicit IBFApplicationService(std::shared_ptr<BFApplication> application);
        ~IBFApplicationService() override = default;

    protected:
        std::shared_ptr<BFApplication> m_application;
    };
}
