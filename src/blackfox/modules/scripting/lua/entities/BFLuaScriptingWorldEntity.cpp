#include "BFLuaScriptingWorldEntity.h"

#include <sol/variadic_args.hpp>
#include <sol/variadic_results.hpp>
#include <sol/object.hpp>
#include <sol/usertype.hpp>
#include <algorithm>

#include "BFWorld.h"
#include "BFApplication.h"
#include "BFLuaComponentSystem.h"
#include "BFLuaRuntimeRegistry.h"
#include "BFLuaEntityArchetype.h"
#include "BFResourcesHolder.h"
#include "BFLuaUtils.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingWorldEntity, "WorldEntity")

namespace BlackFox
{
    /*!
     * Convert variadic arguments to vector. Arguments must be all of the same type.
     *
     * @tparam T        Type of arguments
     * @param args      Variadic arguments
     *
     * @return          The vector
     */
    /*template<typename T>
    std::vector<T> argsToVector(const sol::variadic_args& args)
    {
        std::vector<T> v;
        v.resize(args.size());
        std::transform(args.cbegin(), args.cend(), v.begin(), [&](const auto& a) { return a.template as<T>(); });
        return v;
    }*/

    /*!
     * Create an entity from a list of component ids
     *
     * @param world         The world to use
     * @param container     The DI container
     * @param components    The list of component ids
     * @param state         Sol state
     *
     * @return              Sol variadic results with the entity and an instance of each component
     */
    auto createEntityFromComponentList(
            const BFWorld& world,
            const DiContainer& container,
            const std::vector<ComponentId>& components,
            sol::state* state)
    {
        auto runtimeRegistry = container->get<BFLuaRuntimeRegistry>();
        runtimeRegistry->setEntityManager(world.entityManager());

        const auto entity = world.entityManager()->create();

        sol::variadic_results result;
        result.push_back({ *state, sol::in_place_type<entt::entity>, entity });

        for (const auto& component : components)
        {
            const auto c = runtimeRegistry->setComponent(entity, component, state);
            result.push_back(c);
        }

        return result;
    }

    /*!
     * Create an entity from an archetype
     *
     * @param world         The world to use
     * @param container     The DI container
     * @param archetype     The archetype to use
     * @param state         Sol state
     *
     * @return              Sol variadic results with the entity and an instance of each component contained in the archetype
     */
    auto createEntityFromArchetype(
            const BFWorld& world,
            const DiContainer& container,
            const BFLuaEntityArchetype& archetype,
            sol::state* state)
    {
        return createEntityFromComponentList(world, container, archetype.components(), state);
    }

    /*!
     * Iterate over entities from a list of component ids
     *
     * @param world         The world to use
     * @param container     The DI container
     * @param callback      The callback to call on each entity to perform actions on it
     * @param dt            Delta time
     * @param components    The list of component ids
     * @param state         Sol state
     *
     * @return              The number of matching entities
     */
    size_t iterateEntities(
            const BFWorld& world,
            const DiContainer& container,
            const sol::function& callback,
            const float dt,
            const std::vector<ComponentId>& components,
            sol::state* state)
    {
        try
        {
            auto runtimeRegistry = container->get<BFLuaRuntimeRegistry>();
            runtimeRegistry->setEntityManager(world.entityManager());
            return runtimeRegistry->entities(callback, dt, components, state);
        }
        catch(const std::exception& e)
        {
            BF_ERROR("{}", e.what());
            return 0;
        }
    }

    /*!
     * Iterate over entities matching an archetype
     *
     * @param world         The world to use
     * @param container     The DI container
     * @param callback      The callback to call on each entity to perform actions on it
     * @param dt            Delta time
     * @param archetype     The archetype to filter entities
     * @param state         Sol state
     *
     * @return              The number of matching entities
     */
    size_t iterateArchetype(
            const BFWorld &world,
            const DiContainer &container,
            const sol::function &callback,
            const float dt,
            const BFLuaEntityArchetype &archetype,
            sol::state *state)
    {
        return iterateEntities(world, container, callback, dt, archetype.components(), state);
    }

    //---------------------------------------------------------------

    void BFLuaScriptingWorldEntity::registerEntity()
    {
	    auto componentType = m_namespace.new_usertype<ComponentId>("ComponentId");
	    auto entityType = m_namespace.new_usertype<entt::entity>("Entity");
	    auto worldType = m_namespace.new_usertype<BFWorld>("World");

    	// Archetype
    	auto archetypeType = m_namespace.new_usertype<BFLuaEntityArchetype>("EntityArchetype");

    	worldType["archetypes"] = [&](BFWorld& world, const sol::function& callback, const float dt, const BFLuaEntityArchetype& archetype) -> size_t
        {
            return iterateArchetype(world, m_container, callback, dt, archetype, m_state);
        };

    	worldType["archetype"] = [&](BFWorld& world, const sol::variadic_args& components)
        {
    	    auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
    	    runtimeRegistry->setEntityManager(world.entityManager());

            return std::make_shared<BFLuaEntityArchetype>(Scripting::Lua::argsToVector<ComponentId>(components), runtimeRegistry, m_state);
        };

    	worldType["createArchetype"] = [&](BFWorld& world, const BFLuaEntityArchetype& archetype)
        {
    	    return createEntityFromArchetype(world, m_container, archetype, m_state);
        };

        //Entities

        // Create entity
        worldType["createEntity"] = [&](BFWorld& world, const sol::variadic_args& components)
        {
            return createEntityFromComponentList(world, m_container, Scripting::Lua::argsToVector<ComponentId>(components), m_state);
        };

        // Destroy entity
        worldType["destroyEntity"] = [](BFWorld& world, const entt::entity entity)
        {
            world.entityManager()->destroy(entity);
        };

        // Register component
        worldType["registerComponent"] = [&](const std::string& componentName)
        {
            auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
            const auto cid = runtimeRegistry->registerRuntimeComponent(componentName, fmt::format("components/{}.lua", componentName), m_state);

            sol::table componentsNs = m_namespace["Components"].get_or_create<sol::table>();
            sol::table runtimeNs = componentsNs["Runtime"].get_or_create<sol::table>();

            auto component_t = runtimeNs[componentName].get_or_create<sol::table>();
            component_t["id"] = [=]() -> auto
            {
                return cid;
            };
        };

        // Set component
        worldType["setComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId) -> sol::object
        {
			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
            return runtimeRegistry->setComponent(entity, componentId, m_state);
        };

        // Unset component
		worldType["unsetComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId)
		{
			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			runtimeRegistry->unsetComponent(entity, componentId);
		};

        // Has component
		worldType["hasComponent"] = [&](BFWorld& world, const entt::entity entity, const ComponentId componentId) -> bool
		{
			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			return runtimeRegistry->hasComponent(entity, componentId);
		};
    	
        // Get component
		worldType["getComponent"] = [&](BFWorld& world, const entt::entity& entity, const ComponentId componentId) -> sol::object
		{
			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());
			return runtimeRegistry->getComponent(entity, componentId, m_state);
		};

        // Get components
        worldType["getComponents"] = [&](BFWorld& world, const entt::entity& entity, const sol::variadic_args& components) -> auto
        {
			auto runtimeRegistry = m_container->get<BFLuaRuntimeRegistry>();
			runtimeRegistry->setEntityManager(world.entityManager());

            std::vector<ComponentId> ids(components.cbegin(), components.cend());
            return sol::as_returns(runtimeRegistry->getComponents(m_state, entity, ids));
        };

        // Iterate entities
        worldType["entities"] = [&](BFWorld& world, const sol::function& callback, const float dt, const sol::variadic_args& components) -> size_t
		{
            return iterateEntities(world, m_container, callback, dt, Scripting::Lua::argsToVector<ComponentId>(components), m_state);
		};

        //System
        worldType["createSystem"] = [&](BFWorld& world, const std::string& systemName) -> BFComponentSystem*
        {
            auto resourcesHolder = m_container->get<IBFResourcesHolder>();
            auto handle = resourcesHolder->loadTextAsset(
                    Resources::LUA_SYSTEM_SCRIPT,
                    fmt::format("systems/{}.lua", systemName));

            BFLuaScript::Ptr luaScript = std::make_shared<BFLuaScript>(BFLuaScript::ScriptType::System, handle, m_state);

            std::string errorMessage;
            if(!luaScript->load(&errorMessage))
            {
                BF_ERROR("Failed to create system {} : {}", systemName, errorMessage);
                return nullptr;
            }

            const auto app = m_container->get<BFApplication>();
            const auto system = std::make_shared<BFLuaComponentSystem>(app, world.shared_from_this(), luaScript);

            return world.createSystemFromName(systemName, system, false);
        };

        worldType["hasSystem"] = [&](BFWorld& world, const std::string& systemName) -> bool
        {
            return world.hasSystemByName(systemName);
        };

        worldType["getSystem"] = [&](BFWorld& world, const std::string& systemName) -> BFComponentSystem*
        {
            return world.getSystemByName(systemName);
        };

        //Static methods
        m_namespace["createWorld"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            return BFWorld::create(worldId, m_container);
        };

        m_namespace["getWorld"] = [&](const std::string& worldId) -> BFWorld::Ptr
        {
            return BFWorld::world(worldId);
        };

        m_namespace["hasWorld"] = [&](const std::string& worldId) -> bool
        {
            return BFWorld::hasWorld(worldId);
        };
    }
}