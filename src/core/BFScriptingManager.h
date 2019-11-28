#ifndef BLACKFOX_SCRIPTING_MANAGER_H
#define BLACKFOX_SCRIPTING_MANAGER_H

//#include <chaiscript/chaiscript.hpp>

namespace BlackFox
{
	class BFScriptingManager
	{
	public:
		BFScriptingManager();
		~BFScriptingManager();

		/*template <typename T>
		void registerType(const std::string& typeName)
		{
			m_chai.add(chaiscript::user_type<T>(), typeName);
		}

		template <typename T>
		T evalFile(const std::string& file)
		{
			return m_chai.eval_file<T>(file);
		}

	private:
		chaiscript::ChaiScript m_chai;*/
	};
}

#endif