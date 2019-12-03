#ifndef BLACKFOX_SCRIPTING_MANAGER_H
#define BLACKFOX_SCRIPTING_MANAGER_H

#define SOL_ALL_SAFETIES_ON 1

#include <sol/sol.hpp>
#include <memory>

#include "BFNonCopyable.h"

namespace BlackFox
{
	class BFScriptingManager : private BFNonCopyable
	{
	public:
	    std::shared_ptr<BFScriptingManager> Ptr;

		BFScriptingManager();
		~BFScriptingManager() = default;

		sol::protected_function_result evalScript(const std::string& script);
        sol::protected_function_result evalFile(const std::string& file);

	private:
		sol::state m_state;
	};
}

#endif