#pragma once

#include "BFYamlData.h"
#include <yaml-convert.h>
#include <blackfox/resources/BFResourceTypes.h>

namespace BlackFox::Editor
{
    struct BFResourceData final : BFYamlData<BFResourceData>
    {
        BFResourceData();

		explicit operator std::string() const;
    	
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