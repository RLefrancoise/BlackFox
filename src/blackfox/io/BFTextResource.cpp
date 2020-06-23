#include "BFTextResource.h"
#include <fstream>

namespace BlackFox
{
    BFTextResource::BFTextResource(const Resources::ResourceType& type)
    : BFResource(type)
    {}

    BFTextResource::BFTextResource(BlackFox::BFTextResource && res) noexcept
    : m_content(res.m_content)
    , BFResource(std::move(res))
    {}

    BFTextResource& BFTextResource::operator=(BFTextResource && res) noexcept
    {
        m_content = res.m_content;
        BFResource::operator=(std::move(res));
        return *this;
    }

    bool BFTextResource::save() const
    {
        const std::filesystem::path path = static_cast<std::string>(m_filePath);
        std::ofstream ofs(path);
        if (!ofs.is_open()) return false;

        ofs << content();
        ofs.close();

        return ofs.good();
    }

    bool BFTextResource::load(const std::filesystem::path& file, std::string* errorMessage)
    {
        if(!BFResource::load(file, errorMessage)) return false;

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