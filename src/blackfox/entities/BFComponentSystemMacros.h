#pragma once

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>
#include <entt/entt.hpp>
#include <functional>

#include "BFComponentSystemFlags.h"

namespace BlackFox {
    class BFApplication;
    class BFWorld;
}

template<class S, class Base>
struct register_system
{
    register_system()
    {
        entt::meta<S>().type(entt::hashed_string(S::name))
                .template base<Base>()
                .template ctor<std::shared_ptr<BlackFox::BFApplication>, std::shared_ptr<BlackFox::BFWorld>>()
                .template data<&S::name>("name"_hs)
                .template data<&S::group>("group"_hs);
    }
};

#define BF_SYSTEM(system, systemName, systemGroup)              public: \
                                                                    static constexpr const BlackFox::ComponentSystemGroups group = systemGroup; \
                                                                    static constexpr const char* name = systemName; \

#define BF_SYSTEM_CREATE(system)                                namespace { register_system<system, BlackFox::BFComponentSystem> auto_register_; }


#define BF_SYSTEM_AUTO_CREATE(system, systemGroup, systemName)  RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                                public: \
                                                                    BlackFox::ComponentSystemGroups get_group() const { return group; } \
                                                                    static constexpr const BlackFox::ComponentSystemGroups group = systemGroup; \
                                                                    static constexpr const char* name = systemName;

#ifdef BLACKFOX_SHARED_LIB

#define BF_SYSTEM_REGISTER(system)                              RTTR_PLUGIN_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<system>(system::name) \
                                                                    .constructor<std::shared_ptr<BlackFox::BFApplication>,std::shared_ptr<BlackFox::BFWorld>>()(rttr::policy::ctor::as_raw_ptr) \
                                                                    .method("update", &system::update) \
                                                                    .method("name", []() { return system::name; }) \
                                                                    .method("get_group", &system::get_group); \
                                                                }

#else

#define BF_SYSTEM_REGISTER(system)                              RTTR_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<system>(system::name) \
                                                                    .constructor<std::shared_ptr<BlackFox::BFApplication>,std::shared_ptr<BlackFox::BFWorld>>()(rttr::policy::ctor::as_raw_ptr) \
                                                                    .method("update", &system::update) \
                                                                    .method("name", []() { return system::name; }) \
                                                                    .method("get_group", &system::get_group); \
                                                                }
#endif