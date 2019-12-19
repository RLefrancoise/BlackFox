#pragma once

#include <string>
#include <map>
#include "BFComponent.h"

namespace BlackFox::Components
{
	template<typename Data>
	struct BFRuntimeComponent : BFComponent<BFRuntimeComponent<Data>>
	{
		bool empty()
		{
			return m_components.empty();
		}

		const std::map<unsigned int, Data>& components()
		{
			return m_components;
		}

		Data& get(const unsigned int typeId)
		{
			return m_components[typeId];
		}

		bool has(const unsigned int typeId)
		{
			return m_components.find(typeId) != m_components.end();
		}

		void erase(const unsigned int typeId)
		{
			m_components.erase(typeId);
		}

		void set(const unsigned int typeId, const Data& data)
		{
			m_components[typeId] = data;
		}
	private:
		std::map<unsigned int, Data> m_components;
	};
}