#pragma once

#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "BFDebug.h"

namespace BlackFox::Editor
{
    template<class T>
    class BFYamlData
    {
    public:
        BFYamlData() = default;

        [[nodiscard]] virtual bool save(std::string* errorMessage) const
        {
            std::ofstream ofs(m_file.string(), std::ofstream::out);
            if(!ofs.good()) return false;

            const T& thisP = static_cast<const T&>(*this);
            YAML::Emitter emitter;
            emitter << thisP;

            if(!emitter.good() && !emitter.GetLastError().empty())
            {
                *errorMessage = emitter.GetLastError();
                return false;
            }

            ofs << emitter.c_str();
            ofs.close();

            return true;
        }

        virtual void saveOrThrow()
        {
            std::string err;
            if (!save(&err))
            {
                BF_EXCEPTION("Failed to save YAML data {}: {}", m_file.string(), err);
            }
        }

        [[nodiscard]] virtual bool load(const std::filesystem::path& file, std::string* errorMessage)
        {
            try
            {
                const auto node = YAML::LoadFile(file.string());
                T* thisP = static_cast<T*>(this);
                *thisP = node.as<T>();

                m_file = file;

                return true;
            }
            catch(const std::exception& e)
            {
                *errorMessage = e.what();
                return false;
            }
        }

        virtual void loadOrThrow(const std::filesystem::path& file)
        {
            std::string err;
            if (!load(file, &err))
            {
                BF_EXCEPTION("Failed to load YAML data {}: {}", file.string(), err);
            }
        }

        virtual void file(const std::filesystem::path& file)
        {
            m_file = file;
        }

        virtual const std::filesystem::path& file() const
        {
            return m_file;
        }

    protected:
        std::filesystem::path m_file;
    };
}