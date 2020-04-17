#include "BFEditorData.h"
#include "BFStringUtils.h"

namespace YAML
{
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
}

