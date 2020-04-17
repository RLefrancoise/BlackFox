#pragma once

#include <imgui.h>
#include <yaml-convert.h>
#include <memory>
#include "BFYamlFile.h"

namespace BlackFox::Editor
{
	/**
	 * Editor config
	 */
	struct BFEditorConfig
	{
		/**
		 * Background color
		 */
		ImColor backgroundColor;
	};

	/**
	 * Editor data
	 */
	struct BFEditorData final: BFYamlFile<BFEditorData>
	{
		typedef std::shared_ptr<BFEditorData> Ptr;

		/**
		 * You are not supposed to use the default constructor.
		 * It is here because it is required by YAML to decode from file
		 */
		BFEditorData() = default;
		explicit BFEditorData(const std::filesystem::path& filePath);
		~BFEditorData() = default;
		BFEditorData(const BFEditorData& data) = default;
		BFEditorData& operator=(const BFEditorData& data) = default;
		BFEditorData(BFEditorData&&) = default;
		BFEditorData& operator=(BFEditorData&&) = default;

		explicit operator std::string() const override;
		
		/**
		 * Editor config
		 */
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

	template<>
	struct convert<BlackFox::Editor::BFEditorData>
	{
		static Node encode(const BlackFox::Editor::BFEditorData& data)
		{
			Node node;
			node["config"] = data.config;;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFEditorData& data)
		{
			if (!node.IsMap()) return false;

			if (node["config"]) data.config = node["config"].as<BlackFox::Editor::BFEditorConfig>();

			return true;
		}
	};

	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorConfig& config);
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorData& data);
}