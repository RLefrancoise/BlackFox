#ifndef BLACKFOX_COMPONENTSYSTEMFLAGS_H
#define BLACKFOX_COMPONENTSYSTEMFLAGS_H

#include <typeindex>
#include <vector>
#include <unordered_map>

#include "BFDebug.h"

namespace BlackFox
{
	enum ComponentSystemGroups
	{
		GameLoop		= 1 << 0,
		Render			= 1 << 1,
		EndOfFrame		= 1 << 2
	};

	/*typedef std::unordered_map<ComponentSystemGroups, std::vector<std::type_index> > SystemGroups;
	static SystemGroups systemGroups;

	template <typename System>
	class BFComponentSystemGroupAdder
	{
	public:
		explicit BFComponentSystemGroupAdder(ComponentSystemGroups group)
		{
			BF_PRINT("Component system {} placed in group {}", typeid(System).name(), group)
			systemGroups[group].emplace_back(typeid(System));
		}
	};

#define BF_SYSTEM(system, group)	BFComponentSystemGroupAdder<system> _group_system_ = BFComponentSystemGroupAdder<system>(group);*/
}

#endif