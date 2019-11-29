#ifndef BLACKFOX_COMPONENTSYSTEMMACROS_H
#define BLACKFOX_COMPONENTSYSTEMMACROS_H

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>

#include "BFDebug.h"
#include "BFComponentSystemFlags.h"

namespace BlackFox {
    class BFApplication;
}

#define BF_SYSTEM_AUTO_CREATE(system, group)        RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                    public: \
                                                        explicit system(BlackFox::BFApplication* application): BlackFox::BFComponentSystem(application) \
                                                        { \
                                                            BF_PRINT("{} ctor(BFApplication*)", typeid(this).name()) \
                                                        } \
                                                        BlackFox::ComponentSystemGroups get_group() const { return group; }

#define BF_SYSTEM_REGISTER(system, systemName)      RTTR_REGISTRATION \
                                                    { \
                                                        using namespace rttr; \
                                                        registration::class_<system>(systemName) \
                                                        .constructor<BlackFox::BFApplication*>()(rttr::policy::ctor::as_raw_ptr) \
                                                        .method("onEvent", &system::onEvent) \
                                                        .method("update", &system::update) \
                                                        .method("name", &system::name) \
                                                        .method("setWorld", &system::setWorld) \
                                                        .method("get_group", &system::get_group); \
                                                    }

#endif //BLACKFOX_COMPONENTSYSTEMMACROS_H
