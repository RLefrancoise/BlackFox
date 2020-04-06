#ifndef BLACKFOX_DATAINSTALLER_H
#define BLACKFOX_DATAINSTALLER_H

#include "BFBaseInstaller.h"
#include "BFConfigData.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT BFDataInstaller final : public BFBaseInstaller
    {
    public:
        explicit BFDataInstaller(DiContainer container);
        void installBindings() override;

    private:
        BFConfigData::Ptr m_configData;
    };
}

#endif //BLACKFOX_DATAINSTALLER_H
