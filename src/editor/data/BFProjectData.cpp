#include "BFProjectData.h"
#include "BFStringUtils.h"

using namespace YAML;

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

namespace BlackFox::Editor
{
	std::function<std::string(const std::filesystem::path&)> stringifyPath = [](const std::filesystem::path& p)
	{
		return p.string();
	};

	BFProjectData::BFProjectData() : Super(PROJECT_DATA, "")
	{
	}

	BFProjectData::BFProjectData(const std::filesystem::path& filePath) : Super(PROJECT_DATA, filePath)
	{
	}

	BFProjectData::operator std::string() const
	{		
		return fmt::format(R""""(===Project Data===
name: {}
scenes: {}
)"""", name, Utils::join<std::filesystem::path>(scenes, ',', stringifyPath));
	}

	std::filesystem::path BFProjectData::rootPath() const
	{
		auto p = file();
		return p.remove_filename();
	}
}
