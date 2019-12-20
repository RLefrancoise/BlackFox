#pragma once

#include <string>
#include <map>
#include "BFComponent.h"

namespace BlackFox::Components
{
	template<typename Data>
	struct BFRuntimeComponent : BFComponent<BFRuntimeComponent<Data>>
	{
		bool empty() const
		{
			return m_components.empty();
		}

		const std::map<ENTT_ID_TYPE, Data>& components() const
		{
			return m_components;
		}

		const Data& get(const ENTT_ID_TYPE typeId) const
		{
			return m_components.at(typeId);
		}

		bool has(const ENTT_ID_TYPE typeId) const
		{
			return m_components.find(typeId) != m_components.end();
		}

		void erase(const ENTT_ID_TYPE typeId)
		{
			m_components.erase(typeId);
		}

		void set(const ENTT_ID_TYPE typeId, const Data& data)
		{
			m_components[typeId] = data;
		}
	private:
		std::map<ENTT_ID_TYPE, Data> m_components;
	};
}