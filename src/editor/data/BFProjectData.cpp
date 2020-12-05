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
	std::function<std::string(const std::filesystem::path&)> stringifyPath = [](const std::filesystem::path& p)
	{
		return p.string();
	};

	BFProjectData::BFProjectData() : BFYamlData<BFProjectData>(BFYamlFile(Resources::PROJECT_DATA))
	{
	}

	BFProjectData::operator std::string() const
	{		
		return fmt::format(R""""(===Project Data===
name: {}
scenes: {}
)"""", name, Utils::join<std::filesystem::path>(scenes, ",", stringifyPath));
	}

	std::filesystem::path BFProjectData::rootPath() const
	{
		auto p = m_file.file();
		return p.remove_filename();
	}
}
