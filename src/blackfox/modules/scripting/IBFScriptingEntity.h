#pragma once

#include <memory>
#include <rttr/rttr_enable.h>

#include "BFTypeDefs.h"
#include "BFExport.h"

namespace BlackFox
{
    class BLACKFOX_EXPORT IBFScriptingEntity
    {
        RTTR_ENABLE()
    public:
        typedef std::shared_ptr<IBFScriptingEntity> Ptr;

        explicit IBFScriptingEntity(DiContainer container);
        virtual ~IBFScriptingEntity() = default;

        virtual void registerEntity() = 0;
    protected:
        DiContainer m_container;
    };
}