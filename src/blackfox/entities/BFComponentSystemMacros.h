#ifndef BLACKFOX_COMPONENTSYSTEMMACROS_H
#define BLACKFOX_COMPONENTSYSTEMMACROS_H

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>

#include "BFComponentSystemFlags.h"

namespace BlackFox {
    class BFApplication;
}

#define BF_SYSTEM_AUTO_CREATE(system, group, systemName)        RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                                public: \
                                                                    explicit system(BlackFox::BFApplication* application): BlackFox::BFComponentSystem(application) {} \
                                                                    BlackFox::ComponentSystemGroups get_group() const { return group; } \
                                                                    static constexpr const char* name = systemName;

#define BF_SYSTEM_REGISTER(system)                              RTTR_PLUGIN_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<system>(system::name) \
                                                                    .constructor<BlackFox::BFApplication*>()(rttr::policy::ctor::as_raw_ptr) \
                                                                    .method("update", &system::update) \
                                                                    .method("name", []() { return system::name; }) \
                                                                    .method("setWorld", &system::setWorld) \
                                                                    .method("get_group", &system::get_group); \
                                                                }

#endif //BLACKFOX_COMPONENTSYSTEMMACROS_H