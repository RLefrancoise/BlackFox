#pragma once

#include "BFYamlFile.h"
#include <yaml-convert.h>

namespace BlackFox::Editor
{
    struct BFResourceData final : BFYamlFile<BFResourceData>
    {
        BFResourceData();
        explicit BFResourceData(const std::filesystem::path& file);

		explicit operator std::string() const override;
    	
        Resources::ResourceType type;
    };
}

namespace YAML
{
    template<>
	struct convert<BlackFox::Editor::BFResourceData>
	{
		static Node encode(const BlackFox::Editor::BFResourceData& data)
		{
			Node node;
			node["type"] = data.type;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFResourceData& data)
		{
			if (!node.IsMap()) return false;
            if(!node["type"]) return false;

            data.type = node["type"].as<BlackFox::Resources::ResourceType>();

			return true;
		}
	};

	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFResourceData& data);
}