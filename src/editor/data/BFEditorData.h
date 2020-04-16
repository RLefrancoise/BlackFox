#pragma once

#include <imgui.h>
#include <yaml-convert.h>
#include <memory>
#include "BFYamlFile.h"

namespace BlackFox::Editor
{
	struct BFEditorConfig
	{
		ImColor backgroundColor;
	};
	
	struct BFEditorData final: BFYamlFile<BFEditorData>
	{
		typedef std::shared_ptr<BFEditorData> Ptr;
		
		BFEditorConfig config;
	};
	
}

namespace YAML
{
	template<>
	struct convert<BlackFox::Editor::BFEditorConfig>
	{
		static Node encode(const BlackFox::Editor::BFEditorConfig& config)
		{
			Node node;
			node["backgroundColor"] = config.backgroundColor;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFEditorConfig& config)
		{
			if (!node.IsMap()) return false;

			if (node["backgroundColor"]) config.backgroundColor = node["backgroundColor"].as<ImColor>();

			return true;
		}
	};

	inline Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorConfig& config);
	inline Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorData& data);
}