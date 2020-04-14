#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>

namespace BlackFox
{
	template <class T>
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
			out << static_cast<const T&>(*this);
			
			std::ofstream ofs(file);
			ofs << out.c_str();
			ofs.close();

			return ofs.good();
		}
	};
}