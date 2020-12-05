#include "BFTextResource.h"
#include <fstream>
#include <fmt/format.h>

namespace BlackFox
{
    BFTextResource::BFTextResource(const Resources::ResourceType &type, const ResourceGuid& guid)
    : BFResource(type, guid)
    {}

    BFTextResource::BFTextResource(BlackFox::BFTextResource &&res) noexcept
    : BFResource(std::move(res))
    {
        std::swap(m_content, res.m_content);
    }

    BFTextResource &BFTextResource::operator=(BFTextResource &&res) noexcept
    {
        if(this != &res)
        {
            m_content = res.m_content;
            res.m_content = "";
        }

        return *this;
    }

    bool BFTextResource::save() const
    {
        const std::filesystem::path path = Resources::guidToPath(guid());
        std::ofstream ofs(path);
        if (!ofs.is_open()) return false;

        ofs << content();
        ofs.close();

        return ofs.good();
    }

    bool BFTextResource::load(const std::filesystem::path &file, std::string *errorMessage)
    {
        if (!BFResource::load(file, errorMessage)) return false;

        std::ifstream ifs(file);
        if (!ifs.is_open() || !ifs.good()) {
            *errorMessage = fmt::format("Failed to open file {}", file.string());
            return false;
        }

        const std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        m_content = str;

        ifs.close();

        return true;
    }

    void BFTextResource::content(const std::string &content)
    {
        m_content = content;
    }

    std::string BFTextResource::content() const
    {
        return m_content;
    }
}