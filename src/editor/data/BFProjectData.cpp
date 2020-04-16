#include "BFProjectData.h"

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