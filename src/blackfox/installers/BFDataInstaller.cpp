#include "BFDataInstaller.h"
#include "BFConfigData.h"
#include "BFDebug.h"
#include "BFResourcesHolder.h"

namespace BlackFox
{
    BFDataInstaller::BFDataInstaller(DiContainer container) : BFBaseInstaller(std::move(container))
    {
    }

    void BFDataInstaller::installBindings()
    {
        //Config data
        m_configData = std::make_shared<BFConfigData>(BFIniFile("data/config.ini"));
        BF_PRINT(*m_configData);
        m_container->bind<BFConfigData>().toConstant(m_configData);

        //Resources holder
        m_container->bind<BFResourcesHolder>().toSelf().inSingletonScope();
    }
}