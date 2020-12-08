#include "BFVirtualFileInputStream.h"
#include "BFDebug.h"

namespace BlackFox
{
    BFVirtualFileInputStream::BFVirtualFileInputStream(const std::filesystem::path& path, IBFVirtualFileSystem::Ptr vfs)
    {
        try
        {
            const auto bytesRead = vfs->getBytes(path, &m_buffer);
            open(m_buffer, bytesRead);

            //File is opened
            m_isOpened = true;
        }
        catch(const std::exception& err)
        {
            BF_ERROR(err.what());
            m_isOpened = false;
        }
    }

    BFVirtualFileInputStream::~BFVirtualFileInputStream()
    {
        delete m_buffer;
    }

    bool BFVirtualFileInputStream::isOpened()
    {
        return m_isOpened;
    }

    sf::Int64 BFVirtualFileInputStream::read(void *data, sf::Int64 size)
    {
        if(!isOpened()) return -1;
        return sf::MemoryInputStream::read(data, size);
    }

    sf::Int64 BFVirtualFileInputStream::seek(sf::Int64 position)
    {
        if(!isOpened()) return -1;
        return sf::MemoryInputStream::seek(position);
    }

    sf::Int64 BFVirtualFileInputStream::tell()
    {
        if(!isOpened()) return -1;
        return sf::MemoryInputStream::tell();
    }

    sf::Int64 BFVirtualFileInputStream::getSize()
    {
        if(!isOpened()) return -1;
        return sf::MemoryInputStream::getSize();
    }

    std::string BFVirtualFileInputStream::text()
    {
        if(!isOpened()) BF_EXCEPTION("Stream not opened");

        std::string str;
        str.reserve(getSize());

        if(seek(0) == -1)
        {
            BF_EXCEPTION("Failed to seek stream at position {}", 0);
        }

        const auto bytesRead = read(str.data(), str.size());
        if(bytesRead == -1)
        {
            BF_EXCEPTION("Failed to read stream");
        }

        if(seek(bytesRead) == -1)
        {
            BF_EXCEPTION("Failed to seek stream at position {}", bytesRead);
        }

        return str;
    }
}