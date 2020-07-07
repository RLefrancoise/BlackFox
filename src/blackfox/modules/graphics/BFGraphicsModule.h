#pragma once

#include "IBFApplicationModule.h"

namespace BlackFox::Graphics
{
    class BLACKFOX_EXPORT BFGraphicsModule : public BFApplicationModule
    {
    public:
        explicit BFGraphicsModule(DiContainer container);
        void install(const DiContext& context) override;
    };
}