#ifndef BLACKFOX_WORLD_H
#define BLACKFOX_WORLD_H

#include <memory>
#include <typeinfo>
#include <typeindex>
#include <rttr/variant.h>
#include <vector>
#include <unordered_map>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFNonCopyable.h"
#include "BFComponentSystem.h"
#include "BFComponentSystemFlags.h"

#include <sol/sol.hpp>

namespace BlackFox
{
	class BFApplication;

	/*!
	 * \class	BFWorld
	 *
	 * \brief	BlackFox world.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	24/11/2019
	 */
	class BFWorld : private BFNonCopyable
	{
	public:

		/*!
		 * \typedef	std::shared_ptr<BFWorld> Ptr
		 *
		 * \brief	Alias for BlackFox world pointer
		 */
		typedef std::shared_ptr<BFWorld> Ptr;

		/*!
		 * \typedef	std::unordered_map<std::string, BFWorld::Ptr> WorldList
		 *
		 * \brief	Alias for world list.
		 */
		typedef std::unordered_map<std::string, BFWorld::Ptr> WorldList;
		typedef std::unordered_map<std::string, BFComponentSystem::Ptr> SystemList;
        typedef std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem::Ptr>> SystemGroupList;

		/*!
		 * \fn	explicit BFWorld::BFWorld(DiContainer container);
		 *
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \param	container	The DI container.
		 */
		CINJECT(BFWorld(DiContainer container));

		/*!
		 * \fn	EntityManager BFWorld::entityManager() const;
		 *
		 * \brief	Get the Entity manager
		 *
		 * \author	Renaud Lefrançoise
		 * \date	24/11/2019
		 *
		 * \returns	An EntityManager.
		 */
		EntityManager entityManager() const;

		entt::component getComponentIdentifier(const std::string& componentName) const;
		entt::runtime_view getEntityView(sol::as_table_t<std::vector<entt::component>> components) const;

		/*!
		 * \fn	bool BFApplication::hasWorld(const std::string& worldId);
		 *
		 * \brief	Check if world exists
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	worldId	Identifier for the world.
		 *
		 * \returns	True if world exists, false if not.
		 */
		static bool hasWorld(const std::string& worldId);

		/*!
		 * \fn	BFWorld::Ptr BFApplication::world(const std::string& worldId);
		 *
		 * \brief	Get a world by its identifier.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	worldId	Identifier for the world.
		 *
		 * \returns	A BFWorld::Ptr.
		 */
		static BFWorld::Ptr world(const std::string& worldId);

		static BFWorld::Ptr create(const std::string& worldId, BFApplication* application);

		/*!
		 * \fn	template <typename S> S* BFWorld::createSystem(ComponentSystemGroups group)
		 *
		 * \brief	Creates a system in the world.
		 *
		 * \tparam	S			Type of the system.
		 * \param	group		The group the system will belong to.
		 * \param	application	The application.
		 *
		 * \returns	The created system.
		 */
		template <typename S>
		static S* createSystem(ComponentSystemGroups group, BFApplication* application)
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of createSystem must derive from BFComponentSystem");

			const auto type = rttr::type::get<S>();

			if(hasSystem<S>())
			{
				BF_WARNING("World has already the system {}, create system will return the registered system", type.get_name().to_string())
				return getSystem<S>();
			}

			//Create system
			auto system = std::make_shared<S>(application);
			//Add the system to the system list
			registeredSystems.insert(std::make_pair(type.get_name().to_string(), system));
			//Add the system to its group
			systemGroups[group].emplace_back(system);

			BF_PRINT("System {} created", type.get_name().to_string())

			return system.get();
		}

		static BFComponentSystem* createSystemFromType(const rttr::type& system, BFApplication* application);

		static BFComponentSystem* createSystemFromName(
				const std::string& systemName
				, BFComponentSystem::Ptr system
				, ComponentSystemGroups group
				, bool nameIsType = true);

		static void refreshSystems(ComponentSystemGroups group, const BFApplication* application);

		/*!
		 * \fn	template <typename S> static bool BFWorld::hasSystem()
		 *
		 * \brief	Check if the world has the given system or not
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	True if the world has the system, false if not.
		 */
		template <typename S>
		static bool hasSystem()
		{
			const auto type = rttr::type::get<S>();
			return registeredSystems.find(type.get_name().to_string()) != registeredSystems.end();
		}

		static bool hasSystemByName(const std::string& name, bool nameIsType = true);

		/*!
		 * \fn	template <typename S> static S* BFWorld::getSystem()
		 *
		 * \brief	Gets the given system. Returns null pointer if the system does not exist.
		 *
		 * \tparam	S	Type of the system.
		 *
		 * \returns	The system.
		 */
		template <typename S>
		static S* getSystem()
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of getSystem must derive from BFComponentSystem");

			const auto type = rttr::type::get<S>();

			if (!hasSystem<S>())
			{
				BF_WARNING("World has no system {}. getSystem will return a null pointer", type.get_name().to_string())
				return nullptr;
			}

			return static_cast<S*>(registeredSystems[type.get_name().to_string()].get());
		}

		static BFComponentSystem* getSystemByName(const std::string& name);

	private:
		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;

		/*! \brief	The worlds */
		static WorldList worlds;
		static SystemList registeredSystems;
		static SystemGroupList systemGroups;
	};
}

#endif