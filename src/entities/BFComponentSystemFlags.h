#ifndef BLACKFOX_COMPONENTSYSTEMFLAGS_H
#define BLACKFOX_COMPONENTSYSTEMFLAGS_H

#include <typeindex>
#include <vector>
#include <unordered_map>
#include "BFComponentSystem.h"

namespace BlackFox
{
	enum ComponentSystemGroups
	{
		GameLoop		= 1 << 0,
		Render			= 1 << 1,
		EndOfFrame		= 1 << 2
	};

	typedef std::unordered_map<ComponentSystemGroups, std::vector<std::type_index> > SystemGroups;
	static SystemGroups systemGroups;

#define BF_SYSTEM(system, group)	systemGroups[group].emplace_back(typeid(system)); \
									class system : public BFComponentSystem
}

#endif