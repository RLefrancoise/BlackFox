#pragma once

#include <sol/sol.hpp>

#include "BFComponentSystem.h"
#include "BFLuaScript.h"

namespace BlackFox
{
    /*!
     * BlackFox system for Lua scripting
     */
    class BLACKFOX_EXPORT BFLuaComponentSystem final : public BFComponentSystemBase<BFLuaComponentSystem>
    {
    public:
        /*!
         * Create a new Lua component system
         * @param app       Application
         * @param world     World
         * @param script    Lua script containing the system
         */
        explicit BFLuaComponentSystem(
                std::shared_ptr<BFApplication> app,
                std::shared_ptr<BFWorld> world,
                BFLuaScript::Ptr script);
        BFLuaComponentSystem(BFLuaComponentSystem&& system) noexcept ;
        BFLuaComponentSystem& operator=(BFLuaComponentSystem&& system) noexcept;

        ~BFLuaComponentSystem() override;

        void update(float dt) override;
        int getId() const override;
        const char* getName() const override;
        ComponentSystemGroups getGroup() const override;

    private:

        static entt::id_type systemIdGenerator;

        /// Lua system id
        int m_id;

        /// Lua script containing the system
        BFLuaScript::Ptr m_script;

        /// Lua system name
        sol::optional<std::string>  m_name;

        /// Lua system group
        sol::optional<ComponentSystemGroups>  m_group;

        /// onCreate function of the system
        sol::optional<sol::protected_function> m_onCreateFnc;

        /// onDestroy function of the system
        sol::optional<sol::protected_function> m_onDestroyFnc;

        /// update function of the system
        sol::optional<sol::protected_function> m_updateFnc;
    };
}