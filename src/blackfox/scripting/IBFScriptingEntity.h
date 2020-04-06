#ifndef BLACKFOX_ISCRIPTINGENTITY_H
#define BLACKFOX_ISCRIPTINGENTITY_H

#include <memory>
#include <rttr/rttr_enable.h>
#include "BFTypeDefs.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT IBFScriptingEntity
    {
        RTTR_ENABLE()
    public:
        typedef std::shared_ptr<IBFScriptingEntity> Ptr;

        explicit IBFScriptingEntity(DiContainer container)
        : m_container(std::move(container))
        {
        }

        virtual ~IBFScriptingEntity() = default;

        virtual void registerEntity() = 0;
    protected:
        DiContainer m_container;
    };
}

#endif //BLACKFOX_ISCRIPTINGENTITY_H
