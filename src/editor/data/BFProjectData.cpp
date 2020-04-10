#include "BFProjectData.h"
#include <fstream>

namespace BlackFox::Editor
{
	BFProjectData BFProjectData::load(const std::string& file)
	{
		const auto f = YAML::LoadFile(file);
		return f.as<BFProjectData>();
	}

	bool BFProjectData::save(const std::string& file) const
	{
		YAML::Emitter out;
		out << *this;
		
		std::ofstream ofs(file);
		ofs << out.c_str();

		return ofs.good();
	}
}
