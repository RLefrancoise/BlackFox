#pragma once

#include <sol/state.hpp>
#include <sol/protected_function_result.hpp>
#include <memory>
#include <vector>

#include "BFDebug.h"
#include "BFTypeDefs.h"
#include "BFExport.h"
#include "IBFScriptingLanguage.h"
#include "BFVirtualFileSystem.h"

namespace BlackFox
{
	class IBFScriptingEntity;

	/**
	 * \brief BlackFox scripting manager
	 */
	class BLACKFOX_EXPORT BFScriptingManager
	{
	public:
	    std::shared_ptr<BFScriptingManager> Ptr;

		constexpr BFScriptingManager(const BFScriptingManager& app) = delete;
		constexpr BFScriptingManager& operator=(const BFScriptingManager& app) = delete;
		
		CINJECT(BFScriptingManager(DiContainer container, IBFVirtualFileSystem::Ptr vfs));
		BFScriptingManager(BFScriptingManager&& manager) noexcept;
		BFScriptingManager& operator=(BFScriptingManager&& manager) noexcept;
		~BFScriptingManager() = default;

		void addEntity(std::shared_ptr<IBFScriptingEntity> entity);
		void registerEntities();

		void addLanguage(Scripting::IBFScriptingLanguage::Ptr language);
		void registerLanguages();

		template<typename T>
		T evalScript(const std::string& script)
		{
			auto result = m_state.safe_script(script);
			if(!result.valid())
			{
				std::string resultStr = result;
				BF_EXCEPTION("Result of script not valid: {}", resultStr);
			}
			
			return static_cast<T>(result);
		}

		template<typename T>
		T evalFile(const std::string& file)
		{
			auto result = m_state.safe_script_file(file);
			if (!result.valid())
			{
				const std::string resultStr = result;
				BF_EXCEPTION("Result of file {} not valid: {}", file, resultStr);
			}
			
			return static_cast<T>(result);
		}

	private:

		typedef std::vector<std::shared_ptr<IBFScriptingEntity>> Entities;

		DiContainer m_container;
		IBFVirtualFileSystem::Ptr m_vfs;

		sol::state m_state;
		Entities m_entities;

		///	Languages
		std::vector<Scripting::IBFScriptingLanguage::Ptr> m_languages;
	};
}