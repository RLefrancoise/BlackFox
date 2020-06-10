#include "BFTextResource.h"
#include <fstream>

namespace BlackFox
{
    BFTextResource::BFTextResource(const Resources::ResourceType& type)
    : BFResource(type)
    {}

    bool BFTextResource::save() const
    {
        std::ofstream ofs(m_filePath);
        if (!ofs.is_open()) return false;

        ofs << content();
        ofs.close();

        return ofs.good();
    }

    bool BFTextResource::load(const std::filesystem::path& file, std::string* errorMessage)
    {
        std::ifstream ifs(file);
        if (!ifs.is_open() || !ifs.good())
        {
            *errorMessage = "Failed to open file";
            return false;
        }

        const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        m_content = str;

        ifs.close();

        return true;
    }

    void BFTextResource::content(const std::string& content)
    {
        m_content = content;
    }

    std::string BFTextResource::content() const
    {
        return m_content;
    }
}