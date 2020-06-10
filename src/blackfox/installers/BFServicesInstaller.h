#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox
{
    class BFServicesInstaller final : public BFBaseInstaller
    {
    public:
        explicit BFServicesInstaller(DiContainer container);
        void installBindings() override;
    };
}