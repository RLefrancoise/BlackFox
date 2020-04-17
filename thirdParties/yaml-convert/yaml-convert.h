#pragma once

#include <yaml-cpp/yaml.h>
#include <imgui.h>
#include <filesystem>

namespace YAML
{
    //file system path
    inline Emitter& operator<<(Emitter& out, const std::filesystem::path& path)
    {
        out << path.string();
        return out;
    }
	
	template<>
	struct convert<std::filesystem::path>
	{
		static Node encode(const std::filesystem::path& path)
		{
            Node node;
			node = path.string();
            return node;
		}

		static bool decode(const Node& node, std::filesystem::path& path)
		{
            if (!node.IsScalar()) return false;
            path = node.as<std::string>();
            return true;
		}
	};
	
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

    inline Emitter& operator << (Emitter& out, const ImVec2& v) {
        out << Flow;
        out << BeginSeq << v.x << v.y << EndSeq;
        return out;
    }
	
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

    inline Emitter& operator << (Emitter& out, const ImVec4& v) {
        out << Flow;
        out << BeginSeq << v.x << v.y << v.z << v.w << EndSeq;
        return out;
    }

	//ImColor
	template <>
	struct convert<ImColor>
	{
	    static Node encode(const ImColor &color)
	    {
	        Node node;
	        const ImVec4 v = color;
			node = v;
	        return node;
	    }

	    static bool decode(const Node &node, ImColor &color)
	    {
			if (!node.IsSequence()) return false;

			color = node.as<ImVec4>();
	        return true;
	    }
	};

    inline Emitter& operator << (Emitter& out, const ImColor& c) {
        out << c.Value;
        return out;
    }

}