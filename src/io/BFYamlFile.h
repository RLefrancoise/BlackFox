#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>

namespace BlackFox
{
	template <typename T>
	struct BFYamlFile
	{
		static T load(const std::string& file)
		{
			const auto f = YAML::LoadFile(file);
			return f.as<T>();
		}
		
		[[nodiscard]] bool save(const std::string& file) const
		{
			YAML::Emitter out;
			out << *this;

			std::ofstream ofs(file);
			ofs << out.c_str();

			return ofs.good();
		}
	};
}