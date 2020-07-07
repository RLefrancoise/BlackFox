#include "IBFLanguageModule.h"

namespace BlackFox::Scripting
{
    BFLanguageModule::BFLanguageModule(const char* name, DiContainer container)
    : IBFLanguageModule()
    , m_name(name)
    , m_container(std::move(container))
    {}
}