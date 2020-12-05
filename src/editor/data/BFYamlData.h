#pragma once

#include "BFYamlFile.h"

namespace BlackFox::Editor
{
    template<class T>
    class BFYamlData
    {
    public:
        explicit BFYamlData(const BFYamlFile& file) : m_file(file) {}

        [[nodiscard]] virtual bool save()
        {
            const T& thisP = static_cast<const T&>(*this);
            m_file.from<T>(thisP);
            return m_file.save();
        }

        virtual void saveOrThrow()
        {
            m_file.saveOrThrow();
        }

        [[nodiscard]] virtual bool load(const std::filesystem::path& file, std::string* errorMessage)
        {
            if(!m_file.load(file, errorMessage))
                return false;

            m_file.to<T>(static_cast<T*>(this));
            return true;
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
            m_file.file(file);
        }

        virtual std::filesystem::path file() const
        {
            return m_file.file();
        }

    protected:
        BFYamlFile m_file;
    };
}