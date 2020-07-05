#pragma once

#include <memory>
#include <rttr/rttr_enable.h>
#include <entt/entt.hpp>

#include "BFExport.h"
#include "BFComponentSystemEnums.h"

namespace BlackFox
{
	class BFApplication;
	class BFWorld;

	/*!
	 * \class	BFComponentSystem
	 *
	 * \brief	BlackFox Component System.
	 *
	 * \author	Renaud Lefrançoise
	 * \date	26/11/2019
	 */
	class BLACKFOX_EXPORT BFComponentSystem
	{
		RTTR_ENABLE()

	public:

		/*!
		 * \typedef	std::shared_ptr<BFComponentSystem> Ptr
		 *
		 * \brief	Alias for BlackFox component system pointer.
		 */
		typedef std::shared_ptr<BFComponentSystem> Ptr;

		constexpr BFComponentSystem(const BFComponentSystem& system) = delete;
		constexpr BFComponentSystem& operator=(const BFComponentSystem& system) = delete;
		
		BFComponentSystem(BFComponentSystem&& system) noexcept;
		BFComponentSystem& operator=(BFComponentSystem&& system) noexcept;

		/*!
		 * \brief	Constructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	application	The application.
		 */
		BFComponentSystem(std::shared_ptr<BFApplication> application, std::shared_ptr<BFWorld> world);

		/*!
		 * \fn	virtual BFComponentSystem::~BFComponentSystem() noexcept = default;
		 *
		 * \brief	Destructor
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 */
		virtual ~BFComponentSystem() noexcept = default;

		/*!
		 * \fn	virtual void BFComponentSystem::update(float dt) = 0;
		 *
		 * \brief	Updates the system.
		 *
		 * \author	Renaud Lefrançoise
		 * \date	26/11/2019
		 *
		 * \param	dt	The delta time
		 */
		virtual void update(float dt) = 0;

		/*!
		 * Get system Id.
		 *
		 * @return		System Id
		 */
		virtual int getId() const = 0;

		/*!
		 * Get system name
		 *
		 * @return		System name
		 */
		virtual const char* getName() const = 0;

		/*!
		 * Get system group
		 *
		 * @return		System group
		 */
		virtual ComponentSystemGroups getGroup() const = 0;

		/*!
		 * Is system before the given system in its group ?
		 *
		 * @param system	The system to compare to
		 * @return 			True if the system is before the given system
		 */
		virtual bool isBeforeSystem(const BFComponentSystem& system) const = 0;

		/*!
		 * Is system after the given system in its group ?
		 *
		 * @param system 	The system to compare to
		 * @return 			True if the system is after the given system
		 */
		virtual bool isAfterSystem(const BFComponentSystem& system) const = 0;

	protected:
		/*! \brief	The application */
		std::shared_ptr<BFApplication> m_application;
		/*! \brief	The world owning the system */
		std::shared_ptr<BFWorld> m_world;
	};

	template<typename ...System>
	struct BeforeSystems
	{
		constexpr explicit operator std::array<entt::id_type, sizeof...(System)> () const
		{
			const std::array<entt::id_type, sizeof...(System)> v = { (System::id)... };
			return v;
		}

		constexpr auto toArray() const
		{
			return static_cast<std::array<entt::id_type, sizeof...(System)>>(*this);
		}
	};

	template<typename ...System>
	struct AfterSystems
	{
		constexpr explicit operator std::array<entt::id_type, sizeof...(System)> () const
		{
			const std::array<entt::id_type, sizeof...(System)> v = { (System::id)... };
			return v;
		}

		constexpr auto toArray() const
		{
			return static_cast<std::array<entt::id_type, sizeof...(System)>>(*this);
		}
	};

	/*!
	 * Base template for systems
	 *
	 * @tparam System		System class
	 * @tparam Before 		List of systems this system must execute before
	 * @tparam After 		List of systems this system must execute after
	 */
	template<class System, class Before = BeforeSystems<>, class After = AfterSystems<>>
	class BFComponentSystemBase : public BFComponentSystem
	{
	public:
		using Super = BFComponentSystemBase<System, Before, After>;

		///	The system ID
		static constexpr const auto id = entt::type_info<System>::id();

		///	Before systems
		static constexpr const auto beforeSystems = Before().toArray();

		///	After systems
		static constexpr const auto afterSystems = After().toArray();

		explicit BFComponentSystemBase(
				std::shared_ptr<BFApplication> app,
				std::shared_ptr<BFWorld> world)
		: BFComponentSystem(std::move(app), std::move(world))
		{}

		BFComponentSystemBase(BFComponentSystemBase&&) noexcept = default;
		BFComponentSystemBase& operator=(BFComponentSystemBase&&) noexcept = default;

		int getId() const override { return id; }

		bool isBeforeSystem(const BFComponentSystem& system) const override
		{
			return std::find(beforeSystems.cbegin(), beforeSystems.cend(), system.getId()) != beforeSystems.cend();
		}

		bool isAfterSystem(const BFComponentSystem& system) const override
		{
			return std::find(afterSystems.cbegin(), afterSystems.cend(), system.getId()) != afterSystems.cend();
		}
	};
}