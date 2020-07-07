#pragma once

#include <memory>
#include <typeinfo>
#include <rttr/variant.h>
#include <rttr/type.h>
#include <vector>
#include <unordered_map>
#include <entt/entt.hpp>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFComponentSystem.h"
#include "BFComponentSystemEnums.h"
#include "BFComponentListener.h"

namespace BlackFox
{
	class BFApplication;

	/*!
	 * Blackfox world class
	 */
	class BLACKFOX_EXPORT BFWorld : public std::enable_shared_from_this<BFWorld>
	{
	public:

	    ///	Alias for BlackFox world pointer
		typedef std::shared_ptr<BFWorld> Ptr;

		///	Alias for world list.
		typedef std::unordered_map<std::string, BFWorld::Ptr> WorldList;

		/// Alias for system pointer
		typedef BFComponentSystem::Ptr SystemType;

		/// Alias for system list
		typedef std::unordered_map<std::string, SystemType> SystemList;

        /// Alias for systems by group
        typedef std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem*>> SystemGroupList;

		constexpr BFWorld(const BFWorld& app) = delete;
		constexpr BFWorld& operator=(const BFWorld& app) = delete;
		
		/*!
		 * Constructor
		 *
		 * @param	container	The DI container.
		 */
		CINJECT(BFWorld(DiContainer container));

		~BFWorld() = default;

		BFWorld(BFWorld&& world) noexcept;
		BFWorld& operator=(BFWorld&& world) noexcept;
		
		/*!
		 * Get the Entity manager
		 *
		 * @return	EntityManager associated to this world
		 */
		[[nodiscard]] EntityManager entityManager() const;

		/*!
		 * Check if world exists
		 *
		 * @param	worldId	Identifier for the world.
		 *
		 * @return	True if world exists, false if not.
		 */
		static bool hasWorld(const std::string& worldId);

		/*!
		 * Get a world by its identifier.
		 *
		 * @param	worldId	Identifier for the world.
		 *
		 * @return	Created world
		 */
		static BFWorld::Ptr world(const std::string& worldId);

		/*!
		 * Create a new world
		 *
		 * @param worldId       Id of the world
		 * @param container     DI Container
		 *
		 * @return              The created world
		 */
		static BFWorld::Ptr create(const std::string& worldId, const DiContainer& container);

		/*!
		 * Get all the created worlds
		 *
		 * @return The list of created worlds
		 */
		static std::vector<BFWorld::Ptr> all();

		/*!
		 * Creates a system in the world.
		 *
		 * @tparam	S			Type of the system.
		 * @param	application	The application.
		 *
		 * @return	The created system.
		 */
		template <typename S>
		S* createSystem(std::shared_ptr<BFApplication> application)
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of createSystem must derive from BFComponentSystem");

			if(hasSystem<S>())
			{
				BF_WARNING("World has already the system {}, create system will return the registered system", S::name);
				return getSystem<S>();
			}

			//Create system
			SystemType system = std::make_shared<S>(std::move(application), shared_from_this());

			//Add the system to the system list
			m_registeredSystems.insert(std::make_pair(S::name, system));
			//Add the system to its group
			addSystemToGroup(S::group, system);

			BF_PRINT("System {} created", S::name);

			return system.get();
		}

		/*!
		 * Create a new system from a type
		 *
		 * @param system        Type of the system
		 * @param application   Application
		 *
		 * @return              The created system
		 */
		BFComponentSystem* createSystemFromType(const rttr::type& system, std::shared_ptr<BFApplication> application);

		BFComponentSystem* createSystemFromType(entt::meta_type system, std::shared_ptr<BFApplication> application);

		/*!
		 * Create a new system from a name
		 *
		 * @param systemName        Name of the system
		 * @param system            System to create
		 * @param nameIsType        Name is a type name ?
		 *
		 * @return                  The created system
		 */
		BFComponentSystem* createSystemFromName(
				const std::string& systemName, 
				const BFComponentSystem::Ptr& system, 
				bool nameIsType = true);

		/*!
		 * Refresh all the systems of a given group
		 *
		 * @param group         Group to refresh
		 * @param deltaTime     Delta time
		 */
		void refreshSystems(ComponentSystemGroups group, float deltaTime);

		/*!
		 * Check if the world has the given system or not
		 *
		 * @tparam	S	Type of the system.
		 *
		 * @return	True if the world has the system, false if not.
		 */
		template <typename S>
		bool hasSystem()
		{
			return m_registeredSystems.find(S::name) != m_registeredSystems.end();
		}

		/*!
		 * Check if a system is created, by its name
		 *
		 * @param name          Name of the system
		 * @param nameIsType    Name is a type name ?
		 *
		 * @return              True if system exist, false if not
		 */
		bool hasSystemByName(const std::string& name, bool nameIsType = true);

		/*!
		 * Gets the given system. Returns null pointer if the system does not exist.
		 *
		 * @tparam	S	Type of the system.
		 *
		 * @return	The system.
		 */
		template <typename S>
		S* getSystem()
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of getSystem must derive from BFComponentSystem");

			if (!hasSystem<S>())
			{
				BF_WARNING("World has no system {}. getSystem will return a null pointer", S::name);
				return nullptr;
			}

			return static_cast<S*>(m_registeredSystems[S::name].get());
		}

		/*!
		 * Get a system by its name
		 *
		 * @param name      Name of the system
		 *
		 * @return          The system if found, nullptr if not
		 */
		BFComponentSystem* getSystemByName(const std::string& name);

		/*!
		 * Register a component listener
		 *
		 * @tparam ComponentListener        Type of the listener
		 * @tparam Args                     Type of args to give to the listener
		 *
		 * @param args                      List of arguments to give to the listener
		 *
		 * @return                          The listener
		 */
		template<class ComponentListener, typename... Args>
		std::shared_ptr<ComponentListener> registerComponentListener(Args... args)
		{
			auto listener = std::make_shared<ComponentListener>(m_entityManager.get(), std::forward<Args>(args)...);
			return listener;
		}

	private:

		/*!
		 * Sort the systems inside groups according to before and after requirements.
		 */
		void sortSystems(ComponentSystemGroups group);

		/*!
		 * Add the system to its group
		 * 
		 * @param system 
		 */
		void addSystemToGroup(const BFComponentSystem::Ptr& system);

		/*! \brief	The level DI container */
		DiContainer m_container;
		/*! \brief	The entity manager */
		EntityManager m_entityManager;
		/*! \brief The registered systems */
		SystemList m_registeredSystems;
		/*! \brief Systems by group */
		SystemGroupList m_systemGroups;

		/*! \brief	The worlds */
		static WorldList worlds;
	};
}