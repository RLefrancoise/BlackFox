#include "BFEditorData.h"

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