#pragma once

#include <string>
#include <map>
#include "BFComponent.h"

namespace BlackFox::Components
{
	/// --------------------------------------------------------------------------------
	/// <summary>
	/// BlackFox Runtime component.
	/// Used to store all runtime components for a given scripting language.
	/// </summary>
	/// --------------------------------------------------------------------------------
	template<typename Data>
	struct BFRuntimeComponent : BFComponent<BFRuntimeComponent<Data>>
	{
		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Is component empty ?
		/// </summary>
		/// <returns>True if no runtime components are stored, false otherwise</returns>
		/// --------------------------------------------------------------------------------
		bool empty() const
		{
			return m_components.empty();
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Get the map storing the runtime components.
		/// The key is the component ID, and the value is the data representing the component.
		/// </summary>
		/// <returns>The map storing the runtime components</returns>
		/// --------------------------------------------------------------------------------
		const std::map<ENTT_ID_TYPE, Data>& components() const
		{
			return m_components;
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Gets the data representing the component with the given ID
		/// </summary>
		/// <param name="typeId">ID of the component</param>
		/// <returns>The data representing the component</returns>
		/// --------------------------------------------------------------------------------
		const Data& get(const ENTT_ID_TYPE typeId) const
		{
			return m_components.at(typeId);
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Does the component has the given runtime component stored ?
		/// </summary>
		/// <param name="typeId">ID of the runtime component</param>
		/// <returns>True if the component has the given runtime component, false otherwise</returns>
		/// --------------------------------------------------------------------------------
		bool has(const ENTT_ID_TYPE typeId) const
		{
			return m_components.find(typeId) != m_components.end();
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Erase the runtime component with the given ID
		/// </summary>
		/// <param name="typeId">ID of the runtime component</param>
		/// --------------------------------------------------------------------------------
		void erase(const ENTT_ID_TYPE typeId)
		{
			m_components.erase(typeId);
		}

		/// --------------------------------------------------------------------------------
		/// <summary>
		/// Add or set a runtime component by giving its ID and the its data.
		/// </summary>
		/// <param name="typeId">ID of the runtime component</param>
		/// <param name="data">Data of the runtime component</param>
		/// --------------------------------------------------------------------------------
		void set(const ENTT_ID_TYPE typeId, const Data& data)
		{
			m_components[typeId] = data;
		}
	private:
		/// <summary>Map storing the runtime components and their data</summary>
		std::map<ENTT_ID_TYPE, Data> m_components;
	};
}