#pragma once

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>
#include <entt/core/type_info.hpp>
#include <vector>

#include "BFComponentSystemFlags.h"
#include "BFUtils.h"

namespace BlackFox {
    class BFApplication;
    class BFWorld;
}

template<class ...System>
constexpr decltype(auto) systemTypes()
{
    return std::make_tuple((System::id)...);
}

#define BF_SYSTEM(system, systemName, systemGroup)              public: \
                                                                    static constexpr const auto id = entt::type_info<system>::id(); \
                                                                    static constexpr const BlackFox::ComponentSystemGroups group = systemGroup; \
                                                                    static constexpr const char* name = systemName;

#define BF_SYSTEM_AUTO_CREATE(system, systemGroup, systemName)  RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                                BF_SYSTEM(system, systemName, systemGroup)

#define BF_BEFORE_SYSTEM(...)                                   public: \
                                                                    static constexpr const auto beforeSystems = systemTypes<__VA_ARGS__>();

#define BF_AFTER_SYSTEM(...)                                    public: \
                                                                    static constexpr const auto afterSystems = systemTypes<__VA_ARGS__>();

#ifdef BLACKFOX_SHARED_LIB

#define BF_SYSTEM_REGISTER(system)                              RTTR_PLUGIN_REGISTRATION \
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