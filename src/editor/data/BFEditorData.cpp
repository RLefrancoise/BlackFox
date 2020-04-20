#include "BFEditorData.h"
#include "BFStringUtils.h"

namespace YAML
{
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorProjectHistory& history)
	{
		out << BeginMap;

		//Path
		out << Key << "path" << Value << history.path;
		out << Key << "lastUpdateTime" << Value << history.lastUpdateTime;

		out << EndMap;

		return out;
	}
	
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorConfig& config)
	{
		out << BeginMap;

		//Background Color
		out << Key << "backgroundColor" << Value << config.backgroundColor;

		out << EndMap;

		return out;
	}

	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFEditorData& data)
	{
		out << BeginMap;

		//Projects history
		out << Key << "recentProjects" << Value << data.recentProjects;
		
		//Config
		out << Key << "config" << Value << data.config;

		out << EndMap;

		return out;
	}
}

namespace BlackFox::Editor
{
	BFEditorData::BFEditorData(const std::filesystem::path& filePath) : Super(filePath)
	{
	}

	BFEditorData::operator std::string() const
	{
		return fmt::format(R""""(===Editor Data===
* Config:
	backgroundColor: {}
)"""", Utils::join(std::vector<float>{config.backgroundColor.Value.x, config.backgroundColor.Value.y, config.backgroundColor.Value.z, config.backgroundColor.Value.w}));
	}

	void BFEditorData::addProjectToHistory(const BFEditorProjectHistory& project)
	{
		const auto it = std::find_if(recentProjects.begin(), recentProjects.end(), [project](const BFEditorProjectHistory& p)
		{
			return p.path == project.path;
		});
		
		if (it != recentProjects.cend())
		{
			*it = project;
			BF_PRINT("Update project {}", project.path.string());
		}
		else
		{
			BF_PRINT("Add project {} to history", project.path.string());
			recentProjects.push_back(project);
		}
	}
}

