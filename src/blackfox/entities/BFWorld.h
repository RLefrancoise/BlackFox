#pragma once

#include <memory>
#include <typeinfo>
#include <rttr/variant.h>
#include <rttr/type.h>
#include <vector>
#include <unordered_map>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFComponentSystem.h"
#include "BFComponentSystemFlags.h"
#include "BFComponentListener.h"

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
	class BLACKFOX_EXPORT BFWorld : public std::enable_shared_from_this<BFWorld>
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
		/// <summary>Alias for system list</summary>
		typedef std::unordered_map<std::string, BFComponentSystem::Ptr> SystemList;
        /// <summary>Alias for systems by group</summary>
        typedef std::unordered_map<ComponentSystemGroups, std::vector<BFComponentSystem::Ptr>> SystemGroupList;

		constexpr BFWorld(const BFWorld& app) = delete;
		constexpr BFWorld& operator=(const BFWorld& app) = delete;
		
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

		~BFWorld() = default;

		BFWorld(BFWorld&& world) noexcept;
		BFWorld& operator=(BFWorld&& world) noexcept;
		
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
		[[nodiscard]] EntityManager entityManager() const;

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

		
		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Create a new world
		/// </summary>
		/// <param name="worldId">Id of the world</param>
		/// <param name="container">The DI container</param>
		/// <returns>The created world</returns>
		/// --------------------------------------------------------------------------------
		static BFWorld::Ptr create(const std::string& worldId, DiContainer container);

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Get all the created worlds
		/// </summary>
		/// <returns>The list of created worlds</returns>
		/// --------------------------------------------------------------------------------
		static std::vector<BFWorld::Ptr> all();

		/*!
		 * \brief	Creates a system in the world.
		 *
		 * \tparam	S			Type of the system.
		 * \param	group		The group the system will belong to.
		 * \param	application	The application.
		 *
		 * \returns	The created system.
		 */
		template <typename S>
		S* createSystem(const ComponentSystemGroups group, std::shared_ptr<BFApplication> application)
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of createSystem must derive from BFComponentSystem");

			const auto type = rttr::type::get<S>();

			if(hasSystem<S>())
			{
				warning("World has already the system {}, create system will return the registered system", type.get_name().to_string());
				return getSystem<S>();
			}

			//Create system
			auto system = std::make_shared<S>(application, shared_from_this());
			//Add the system to the system list
			m_registeredSystems.insert(std::make_pair(type.get_name().to_string(), system));
			//Add the system to its group
			m_systemGroups[group].emplace_back(system);

			BF_PRINT("System {} created", type.get_name().to_string());

			return system.get();
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Creates a new system from a type.
		/// </summary>
		/// <param name="system">Type of the system</param>
		/// <param name="application">Application</param>
		/// <returns>The created system</returns>
		/// --------------------------------------------------------------------------------
		BFComponentSystem* createSystemFromType(const rttr::type& system, std::shared_ptr<BFApplication> application);


		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Creates a new system from a name
		/// </summary>
		/// <param name="systemName">Name of the system</param>
		/// <param name="system">System to register</param>
		/// <param name="group">Group of the system</param>
		/// <param name="nameIsType">Name is a type name ?</param>
		/// <returns>The created system</returns>
		/// --------------------------------------------------------------------------------
		BFComponentSystem* createSystemFromName(
				const std::string& systemName
				, BFComponentSystem::Ptr system
				, ComponentSystemGroups group
				, bool nameIsType = true);

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Refresh all the systems of a given group.
		/// </summary>
		/// <param name="group">Group to refresh</param>
		/// <param name="deltaTime">Delta time</param>
		/// --------------------------------------------------------------------------------
		void refreshSystems(ComponentSystemGroups group, float deltaTime);

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
		bool hasSystem()
		{
			const auto type = rttr::type::get<S>();
			return m_registeredSystems.find(type.get_name().to_string()) != m_registeredSystems.end();
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Check if a system is created, by its name
		/// </summary>
		/// <param name="name">Name of the system</param>
		/// <param name="nameIsType">Name is a type name ?</param>
		/// <returns>True if system exist, false if not</returns>
		/// --------------------------------------------------------------------------------
		bool hasSystemByName(const std::string& name, bool nameIsType = true);

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
		S* getSystem()
		{
			static_assert(std::is_base_of<BFComponentSystem, S>::value, "Type parameter of getSystem must derive from BFComponentSystem");

			const auto type = rttr::type::get<S>();

			if (!hasSystem<S>())
			{
				BF_WARNING("World has no system {}. getSystem will return a null pointer", type.get_name().to_string());
				return nullptr;
			}

			return static_cast<S*>(m_registeredSystems[type.get_name().to_string()].get());
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Get a system by its name
		/// </summary>
		/// <param name="name">Name of the system</param>
		/// <returns>The system if found, nullptr if not</returns>
		/// --------------------------------------------------------------------------------
		BFComponentSystem* getSystemByName(const std::string& name);

		template<class ComponentListener, typename... Args>
		std::shared_ptr<ComponentListener> registerComponentListener(Args... args)
		{
			auto listener = std::make_shared<ComponentListener>(args...);
			registerComponentListener<ComponentListener>(listener.get());
			
			return listener;
		}

		template<class ComponentListener>
		void registerComponentListener(ComponentListener* listener)
		{
			m_entityManager->on_construct<typename ComponentListener::ComponentType>().template connect<&ComponentListener::onCreate>(*listener);
			m_entityManager->on_replace<typename ComponentListener::ComponentType>().template connect<&ComponentListener::onReplace>(*listener);
			m_entityManager->on_destroy<typename ComponentListener::ComponentType>().template connect<&ComponentListener::onDestroy>(*listener);
		}

	private:
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