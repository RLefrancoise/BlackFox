#pragma once

#include <imgui.h>
#include <yaml-convert.h>
#include <memory>
#include <ctime>
#include <entt/core/hashed_string.hpp>

#include "BFStringUtils.h"
#include "BFYamlData.h"

namespace BlackFox::Editor
{
	namespace Icons
	{
		constexpr static entt::hashed_string FOLDER_ICON = "icons/folder.png"_hs;
		constexpr static entt::hashed_string FILE_ICON = "icons/file.png"_hs;
	}
	
	/**
	 * Editor project history
	 */
	struct BFEditorProjectHistory
	{
		BFEditorProjectHistory() : lastUpdateTime(0) {}

		bool operator==(const BFEditorProjectHistory& h) const
		{
			return path == h.path;
		}

		bool operator>(const BFEditorProjectHistory& h) const
		{
			return lastUpdateTime > h.lastUpdateTime;
		}
		
		/**
		 * Path of the project
		 */
		std::filesystem::path path;
		
		/**
		 * Last update time of the project
		 */
		std::time_t lastUpdateTime;
	};
	
	/**
	 * Editor config
	 */
	struct BFEditorConfig
	{
		/**
		 * Resources path for the editor
		 */
		std::filesystem::path resourcesPath;
		
		/**
		 * Background color
		 */
		ImColor backgroundColor;

		explicit operator std::string() const
		{
			return fmt::format("resourcesPath: {}\nbackgroundColor: {}\n"
				, resourcesPath.string()
				, static_cast<std::string>(Utils::join(
						std::vector<float>{backgroundColor.Value.x, backgroundColor.Value.y, backgroundColor.Value.z, backgroundColor.Value.w})));
		}
	};

	/**
	 * Editor data
	 */
	struct BFEditorData final: BFYamlData<BFEditorData>
	{
		typedef std::shared_ptr<BFEditorData> Ptr;

		BFEditorData();
		~BFEditorData() = default;
		BFEditorData(const BFEditorData& data) = default;
		BFEditorData& operator=(const BFEditorData& data) = default;
		BFEditorData(BFEditorData&&) = default;
		BFEditorData& operator=(BFEditorData&&) = default;

		explicit operator std::string() const;

		/**
		 * Add project to editor history.
		 * 
		 * \param project	Project to add.
		 */
		void addProjectToHistory(const BFEditorProjectHistory& project);

		/**
		 * Recent projects opened in the editor
		 */
		std::vector<BFEditorProjectHistory> recentProjects;
		
		/**
		 * Editor config
		 */
		BFEditorConfig config;
	};
	
}

namespace YAML
{
	template<>
	struct convert<BlackFox::Editor::BFEditorProjectHistory>
	{
		static Node encode(const BlackFox::Editor::BFEditorProjectHistory& h)
		{
			Node node;
			node["path"] = h.path;
			node["lastUpdateTime"] = h.lastUpdateTime;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFEditorProjectHistory& h)
		{
			if (!node.IsMap()) return false;
			if (!node["path"]) return false;

			h.path = node["path"].as<std::filesystem::path>();
			if (node["lastUpdateTime"]) h.lastUpdateTime = node["lastUpdateTime"].as<std::time_t>();

			return true;
		}
	};
	
	template<>
	struct convert<BlackFox::Editor::BFEditorConfig>
	{
		static Node encode(const BlackFox::Editor::BFEditorConfig& config)
		{
			Node node;
			node["resourcesPath"] = config.resourcesPath;
			node["backgroundColor"] = config.backgroundColor;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFEditorConfig& config)
		{
			if (!node.IsMap()) return false;

			if (node["resourcesPath"]) config.resourcesPath = node["resourcesPath"].as<std::filesystem::path>();
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
			node["recentProjects"] = data.recentProjects;
			node["config"] = data.config;;

			return node;
		}

		static bool decode(const Node& node, BlackFox::Editor::BFEditorData& data)
		{
			if (!node.IsMap()) return false;

			if (node["recentProjects"]) data.recentProjects = node["recentProjects"].as<std::vector<BlackFox::Editor::BFEditorProjectHistory>>();
			if (node["config"]) data.config = node["config"].as<BlackFox::Editor::BFEditorConfig>();

			return true;
		}
	};

	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorProjectHistory& history);
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorConfig& config);
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorData& data);
}