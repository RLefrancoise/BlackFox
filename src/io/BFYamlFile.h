#pragma once

#include <string>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>

#include "BFDebug.h"

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

		static bool tryLoad(const std::string& file, T& data)
		{
			try
			{
				data = load(file);
				return true;
			}
			catch(const std::exception& err)
			{
				BF_ERROR(err.what());
				return false;
			}
		}
		
		[[nodiscard]] bool save(const std::string& file) const
		{
			YAML::Emitter out;
			out << static_cast<const T&>(*this);
			
			std::ofstream ofs(file);
			if (!ofs.is_open()) return false;
			
			ofs << out.c_str();
			ofs.close();

			return ofs.good();
		}
	};
}