#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>

#include "BFComponentSystemMacros.h"
#include "BFComponentSystem.h"
#include "Box2D/Dynamics/b2World.h"

namespace BlackFox {
	namespace Components {
		struct BFTransformComponent;
		struct BFRigidBodyComponent;
		struct BFBoxColliderComponent;
	}
}

namespace BlackFox::Systems
{
	class BLACKFOX_EXPORT BFPhysicsSystem final: public BFComponentSystem
	{
		BF_SYSTEM_AUTO_CREATE(BFPhysicsSystem, ComponentSystemGroups::FixedTime, "PhysicsSystem")

		CINJECT(BFPhysicsSystem(std::shared_ptr<BFApplication> app, std::shared_ptr<BFWorld> world));
		void update(float dt) override;

	private:
		struct IWorldRegistryEvents
		{
			explicit IWorldRegistryEvents(const std::type_index t) : type(t) {}

			std::type_index type;
			virtual ~IWorldRegistryEvents() = default;
		};

		template<class Component>
		struct WorldRegistryEvents : IWorldRegistryEvents
		{
			typedef entt::sink<void(entt::entity, entt::registry&, Component&)> ConstructEvent;
			typedef entt::sink<void(entt::entity, entt::registry&)> DestroyEvent;
			typedef entt::sink<void(entt::entity, entt::registry&, Component&)> ReplaceEvent;

			explicit WorldRegistryEvents(ConstructEvent construct, const DestroyEvent destroy, ReplaceEvent replace)
				: IWorldRegistryEvents(typeid(Component))
				, construct(construct)
				, destroy(destroy)
				, replace(replace)
			{}

			virtual ~WorldRegistryEvents()
			{
				construct.disconnect();
				destroy.disconnect();
				replace.disconnect();
			}

			ConstructEvent construct;
			DestroyEvent destroy;
			ReplaceEvent replace;
		};

		template<class Component, auto Construct, auto Destroy, auto Replace>
		void registerComponentListener(
			BFWorld* world,
			const EntityManager& em)
		{
			if(m_worldsRegistryEvents.find(world) == m_worldsRegistryEvents.end())
			{
				m_worldsRegistryEvents.insert(std::make_pair(world, std::vector<IWorldRegistryEvents>()));
			}

			auto eventList = m_worldsRegistryEvents[world];
			const auto findCb = [&](const IWorldRegistryEvents& item) -> auto { return item.type.hash_code() == typeid(Component).hash_code(); };

			if(std::find_if(eventList.begin(), eventList.end(), findCb) != eventList.end())
				return;

			auto construct = em->on_construct<Component>();
			auto destroy = em->on_destroy<Component>();
			auto replace = em->on_replace<Component>();
			
			construct.connect<Construct>(*this);
			destroy.connect<Destroy>(*this);
			replace.connect<Replace>(*this);
			
			m_worldsRegistryEvents[world].emplace_back(WorldRegistryEvents<Component>(construct, destroy, replace));
		}
		
		void listenRigidBodies();
		void listenBoxColliders();
		
		void initRigidBody(entt::entity e, entt::registry& em, Components::BFRigidBodyComponent& rb) const;
		void cleanRigidBody(entt::entity e, entt::registry& em) const;

		void initBoxCollider(entt::entity e, entt::registry& em, Components::BFBoxColliderComponent& box) const;
		void cleanBoxCollider(entt::entity e, entt::registry& em) const;

		void beforeStep(const EntityManager& em);
		void afterStep(const EntityManager& em);
		
		void synchronizeBody(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		void synchronizeTransform(Components::BFRigidBodyComponent& rb, Components::BFTransformComponent& transform);
		
		std::unique_ptr<b2World> m_b2World;
		std::unordered_map<BFWorld*, std::vector<IWorldRegistryEvents>> m_worldsRegistryEvents;
	};
}
