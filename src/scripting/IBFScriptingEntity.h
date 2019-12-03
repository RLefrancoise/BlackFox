#ifndef BLACKFOX_ISCRIPTINGENTITY_H
#define BLACKFOX_ISCRIPTINGENTITY_H

#include <memory>
#include <rttr/rttr_enable.h>

namespace BlackFox
{
    class IBFScriptingEntity
    {
        RTTR_ENABLE()

    public:
        typedef std::shared_ptr<IBFScriptingEntity> Ptr;

        virtual void registerEntity() = 0;
    };
}

#endif //BLACKFOX_ISCRIPTINGENTITY_H
