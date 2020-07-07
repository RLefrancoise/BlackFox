#pragma once

#include <sol/table.hpp>
#include <sol/state.hpp>

#include "IBFLanguageModule.h"
#include "BFLuaRuntimeRegistry.h"

namespace BlackFox::Scripting::Lua
{
    /*!
     * BlackFox Lua module base class
     */
    class BLACKFOX_EXPORT BFLuaModule : public BFLanguageModule
    {
    protected:
        /*!
         * Constructor
         *
         * @param name              Name of the module
         * @param container         DI container
         * @param state             Sol state
         * @param parentNamespace   Parent namespace
         */
        explicit BFLuaModule(
                const char* name,
                DiContainer container,
                sol::state* state,
                sol::table& parentNamespace);

        /*!
         * Register a component type
         *
         * @tparam C            Type of the component
         * @tparam Parents      Parents type of the component
         *
         * @return              Sol user type representing with the component
         */
        template <class C, class ...Parents>
        sol::usertype<C> registerComponentType()
        {
            auto component_t = m_namespace.new_usertype<C>(
                    C::name,
                    sol::base_classes,
                    sol::bases<Parents...>());
            component_t["id"] = []() { return C::id; };

            //Register component to Lua runtime registry
            auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
            runtimeRegistry->registerComponent<C>();

            return component_t;
        }

        /// Sol state
        sol::state* m_state;
        /// Module namespace
        sol::table m_namespace;
    };
}
