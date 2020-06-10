#pragma once

#include <rttr/rttr_enable.h>
#include <rttr/registration.h>

#include "BFComponentSystemFlags.h"

namespace BlackFox {
    class BFApplication;
}

#define BF_SYSTEM_AUTO_CREATE(system, group, systemName)        RTTR_ENABLE(BlackFox::BFComponentSystem) \
                                                                public: \
                                                                    BlackFox::ComponentSystemGroups get_group() const { return group; } \
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