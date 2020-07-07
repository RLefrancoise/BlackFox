#include "BFGraphicsModule.h"

namespace BlackFox::Graphics
{

    BFGraphicsModule::BFGraphicsModule(DiContainer container)
    : BFApplicationModule(std::move(container))
    {}

    void BFGraphicsModule::install(const DiContext &context)
    {
    }
}