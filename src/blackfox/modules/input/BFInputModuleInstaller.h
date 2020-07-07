#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox::Input
{
    class BLACKFOX_EXPORT BFInputModuleInstaller : public BFBaseInstaller
    {
    public:
        explicit BFInputModuleInstaller(DiContainer container);

        void installBindings() override;
    };
}