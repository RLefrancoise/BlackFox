#ifndef BLACKFOX_SCRIPTING_MANAGER_H
#define BLACKFOX_SCRIPTING_MANAGER_H

#include <falcon/engine.h>

namespace BlackFox
{
	class ScriptingManager
	{
	public:
		ScriptingManager();
		~ScriptingManager();
		int embed(const char* scriptName);
		Falcon::Module* createAppModule();
	};
}

#endif