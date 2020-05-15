#pragma once

#include <filesystem>
#include "BFYamlFile.h"
#include <yaml-convert.h>

namespace BlackFox::Editor
{
	/**
	 * Project data
	 */
	struct BFProjectData final: BFYamlFile<BFProjectData>
	{		
		typedef std::shared_ptr<BFProjectData> Ptr;

		BFProjectData();

		explicit operator std::string() const override;

		/**
		 * Get the root path of the project.
		 * 
		 * \return The root path of the project
		 */
		[[nodiscard]] std::filesystem::path rootPath() const;
		
		/**
		 * Project name
		 */
		std::string name;
		
		/**
		 * Scenes contained in the project
		 */
		std::vector<std::filesystem::path> scenes;
	};
}

namespace YAML
{
	template<>
	struct convert<BlackFox::Editor::BFProjectData>
	{
		static Node encode(const BlackFox::Editor::BFProjectData& projectData)
		{
			Node node;
			node["name"] = projectData.name;
			node["scenes"] = projectData.scenes;
			
			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFProjectData& projectData)
		{
			if (!node.IsMap()) return false;
			if (!node["name"]) return false;
			if (!node["scenes"]) return false;
			
			projectData.name = node["name"].as<std::string>();
			projectData.scenes = node["scenes"].as <std::vector<std::filesystem::path>>();

			return true;
		}
	};
}

YAML::Emitter& operator<<(YAML::Emitter& out, const BlackFox::Editor::BFProjectData& data);