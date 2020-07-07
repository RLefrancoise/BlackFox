#include "IBFScriptingEntity.h"

namespace BlackFox
{
    IBFScriptingEntity::IBFScriptingEntity(DiContainer container)
    : m_container(std::move(container))
    {
    }
}