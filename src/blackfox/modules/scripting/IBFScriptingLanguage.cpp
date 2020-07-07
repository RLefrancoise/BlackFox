#include "IBFScriptingLanguage.h"

namespace BlackFox::Scripting
{
    BFScriptingLanguage::BFScriptingLanguage(DiContainer container)
    : m_container(std::move(container))
    {}

    void BFScriptingLanguage::addModule(IBFLanguageModule::Ptr module)
    {
        m_modules.emplace_back(std::move(module));
    }

    void BFScriptingLanguage::use()
    {
        for(const auto& module : m_modules)
            module->registerModule();
    }
}