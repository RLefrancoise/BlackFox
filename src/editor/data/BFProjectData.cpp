#include "BFProjectData.h"
#include "BFStringUtils.h"

namespace YAML
{
	Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFProjectData& data)
	{
		out << BeginMap;

		//Name
		out << Key << "name" << Value << data.name;

		//Scenes
		out << Key << "scenes" << Value << data.scenes;

		out << EndMap;

		return out;
	}
}

namespace BlackFox::Editor
{
	BFProjectData::BFProjectData() : BFYamlData<BFProjectData>()
	{
	}

	BFProjectData::operator std::string() const
	{		
		return fmt::format(R""""(===Project Data===
name: {}
scenes: {}
)"""", name, static_cast<std::string>(Utils::join<std::filesystem::path>(scenes, ",", Utils::stringifyPath)));
	}

	std::filesystem::path BFProjectData::rootPath() const
	{
		auto p = m_file;
		return p.remove_filename();
	}
}
