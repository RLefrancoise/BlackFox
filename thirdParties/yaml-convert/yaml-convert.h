#pragma once

#include <yaml-cpp/yaml.h>
#include <imgui.h>

namespace YAML
{
    // ImVec2
    template <>
    struct convert<ImVec2>
    {
        static Node encode(const ImVec2& vec2)
        {
            Node node;
            node.push_back(vec2.x);
            node.push_back(vec2.y);

            return node;
        }

        static bool decode(const Node& node, ImVec2& vec2)
        {
            if (!node.IsSequence() || node.size() != 4)
            {
                return false;
            }

            vec2.x = node[0].as<float>();
            vec2.y = node[1].as<float>();
            return true;
        }
    };
	
	// ImVec4
    template <>
    struct convert<ImVec4>
    {
        static Node encode(const ImVec4& vec4)
        {
            Node node;
			node.push_back(vec4.x);
			node.push_back(vec4.y);
			node.push_back(vec4.z);
			node.push_back(vec4.w);
        	
            return node;
        }

        static bool decode(const Node& node, ImVec4& vec4)
        {
            if (!node.IsSequence() || node.size() != 4)
            {
                return false;
            }

            vec4.x = node[0].as<float>();
            vec4.y = node[1].as<float>();
            vec4.z = node[2].as<float>();
            vec4.w = node[3].as<float>();
            return true;
        }
    };

	//ImColor
	template <>
	struct convert<ImColor>
	{
	    static Node encode(const ImColor &color)
	    {
	        Node node;
	        const ImU32 v = color;
			node = v;
	        return node;
	    }

	    static bool decode(const Node &node, ImColor &color)
	    {
			if (!node.IsScalar()) return false;

			color = node.as<ImU32>();
	        return true;
	    }
	};

}
