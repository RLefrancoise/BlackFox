#include "BFDataInstaller.h"

namespace BlackFox
{
    BFDataInstaller::BFDataInstaller(DiContainer container) : BFBaseInstaller(std::move(container))
    {
    }

    void BFDataInstaller::installBindings()
    {
        //Config data
        m_configData = std::make_shared<BFConfigData>(BFIniFile("data/config.ini"));
        BF_PRINT("{}", (std::string) *m_configData)
        m_container->bind<BFConfigData>().toConstant(m_configData);
    }
}