#include "IBFApplicationService.h"
#include "BFApplication.h"

namespace BlackFox
{
    IBFApplicationService::IBFApplicationService(std::shared_ptr<BFApplication> application)
    : IBFService()
    , m_application(std::move(application))
    {}
}