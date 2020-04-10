#include "BFEditorConfig.h"

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
}