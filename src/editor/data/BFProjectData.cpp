#include "BFProjectData.h"

using namespace YAML;

Emitter& operator<<(Emitter& out, const BlackFox::Editor::BFProjectData& data)
{
	out << BeginMap;

	//Name
	out << Key << "name" << Value << data.name;

	//Scenes
	out << Key << "scenes";
	out << Value << BeginSeq;
	for (const auto& scene : data.scenes)
	{
		out << scene;
	}
	out << EndSeq;

	out << EndMap;

	return out;
}