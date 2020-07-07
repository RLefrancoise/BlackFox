#pragma once

#include "IBFApplicationModule.h"

namespace BlackFox::Scripting
{
    class BLACKFOX_EXPORT BFScriptingModule : public BFApplicationModule
    {
    public:
        explicit BFScriptingModule(DiContainer container);
        void install(const DiContext& context) override;

        void onInit() override;
    };
}