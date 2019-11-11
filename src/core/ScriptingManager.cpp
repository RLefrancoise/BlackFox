#include "ScriptingManager.h"

namespace BlackFox
{
	ScriptingManager::ScriptingManager()
	{
		Falcon::Engine::Init();
	}

	ScriptingManager::~ScriptingManager()
	{
		Falcon::Engine::Shutdown();
	}

	int ScriptingManager::embed(const char* scriptName)
	{
		Falcon::ModuleLoader loader(".");
		loader.addFalconPath();

		Falcon::Runtime rt(&loader);
		rt.loadFile(scriptName);

		Falcon::VMachineWrapper vm;
		vm->link(Falcon::core_module_init());
		vm->link(&rt);
		vm->launch();

		return 0;
	}

	Falcon::Module* ScriptingManager::createAppModule()
	{
		auto module = new Falcon::Module;
		module->name("BlackFox");

		module->addConstant("ZEROVAL", static_cast<Falcon::int64>(0));
		module->addConstant("APP_REFRESH_BACKWARD", static_cast<Falcon::int64>(1));

		return module;
	}
}