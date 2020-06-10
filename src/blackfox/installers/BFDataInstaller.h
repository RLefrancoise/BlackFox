#pragma once

#include "BFBaseInstaller.h"

namespace BlackFox
{
    class BFConfigData;

    class BLACKFOX_EXPORT BFDataInstaller final : public BFBaseInstaller
    {
    public:
        explicit BFDataInstaller(DiContainer container);
        void installBindings() override;

    private:
        std::shared_ptr<BFConfigData> m_configData;
    };
}