#pragma once

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>
#include <entt/core/type_info.hpp>
#include <array>

#include "BFComponentSystemEnums.h"
#include "BFUtils.h"

namespace BlackFox {
    class BFApplication;
    class BFWorld;
}

template<class ...System>
constexpr decltype(auto) systemTypes()
{
    const std::array<entt::id_type, sizeof...(System)> v = { (System::id)... };
    return v;
}

#define BF_SYSTEM(system, systemName, systemGroup)                                                                  \
                                                                                                                    \
public:                                                                                                             \
    static constexpr const char* name = systemName;                                                                 \
    const char* getName() const override { return name; }                                                           \
    static constexpr const BlackFox::ComponentSystemGroups group = systemGroup;                                     \
    BlackFox::ComponentSystemGroups getGroup() const override { return group; }

#define BF_SYSTEM_AUTO_CREATE(system, systemGroup, systemName)  RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                                BF_SYSTEM(system, systemName, systemGroup)

#ifdef BLACKFOX_SHARED_LIB

#define BF_SYSTEM_REGISTER(system)                              \
                                                                \
RTTR_PLUGIN_REGISTRATION \
{ \
    using namespace rttr; \
    registration::class_<system>(system::name) \
    .constructor<std::shared_ptr<BlackFox::BFApplication>,std::shared_ptr<BlackFox::BFWorld>>()(rttr::policy::ctor::as_raw_ptr) \
    .method("update", &system::update) \
    .method("id", []() { return system::id; }) \
    .method("name", []() { return system::name; }) \
    .method("group", []() { return system::group; }); \
}

#else

#define BF_SYSTEM_REGISTER(system)                              RTTR_REGISTRATION \
                                                                { \
                                                                    using namespace rttr; \
                                                                    registration::class_<system>(system::name) \
                                                                    .constructor<std::shared_ptr<BlackFox::BFApplication>,std::shared_ptr<BlackFox::BFWorld>>()(rttr::policy::ctor::as_raw_ptr) \
                                                                    .method("update", &system::update) \
                                                                    .method("id", []() { return system::id; }) \
                                                                    .method("name", []() { return system::name; }) \
                                                                    .method("get_group", &system::get_group); \
                                                                }
#endif