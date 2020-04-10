#pragma once

#include <imgui.h>
#include <yaml-convert.h>
#include "BFYamlFile.h"

namespace BlackFox::Editor
{
	struct BFEditorConfig : BFYamlFile<BFEditorConfig>
	{
		ImColor backgroundColor;
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
			if (!node["backgroundColor"]) return false;

			config.backgroundColor = node["backgroundColor"].as<ImColor>();

			return true;
		}
	};

	inline Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorConfig& config);
}