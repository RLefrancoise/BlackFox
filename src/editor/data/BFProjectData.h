#pragma once
#include <string>
#include <yaml-cpp/yaml.h>

namespace BlackFox::Editor
{
	struct BFProjectData
	{
		typedef std::shared_ptr<BFProjectData> Ptr;
		
		std::string name;
		std::vector<std::string> scenes;

		static BFProjectData load(const std::string& file);
		[[nodiscard]] bool save(const std::string& file) const;
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
			projectData.scenes = node["scenes"].as <std::vector<std::string>>();

			return true;
		}
	};

	inline Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFProjectData& data)
	{
		out << BeginMap;
		
		//Name
		out << Key << "name" << Value << data.name;
		
		//Scenes
		out << Key << "scenes";
		out << Value << BeginSeq;
		for(const auto& scene : data.scenes)
		{
			out << scene;
		}
		out << EndSeq;
		
		out << EndMap;
		
		return out;
	}
}