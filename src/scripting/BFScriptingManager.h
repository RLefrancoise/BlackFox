#ifndef BLACKFOX_SCRIPTING_MANAGER_H
#define BLACKFOX_SCRIPTING_MANAGER_H

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include <memory>

#include "common/BFNonCopyable.h"
#include "BFTypeDefs.h"

namespace BlackFox
{
	class IBFScriptingEntity;

	class BFScriptingManager : private BFNonCopyable
	{
	public:
	    std::shared_ptr<BFScriptingManager> Ptr;

		CINJECT(BFScriptingManager(DiContainer container));
		~BFScriptingManager() = default;

		void addEntity(std::shared_ptr<IBFScriptingEntity> entity);
		void registerEntities();

		sol::protected_function_result evalScript(const std::string& script);
        sol::protected_function_result evalFile(const std::string& file);

	private:
		DiContainer m_container;
		sol::state m_state;
		std::vector<std::shared_ptr<IBFScriptingEntity>> m_entities;
	};
}

#endif