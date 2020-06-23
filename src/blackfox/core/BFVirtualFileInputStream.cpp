#include "BFVirtualFileInputStream.h"
#include "BFDebug.h"

namespace BlackFox
{
    BFVirtualFileInputStream::BFVirtualFileInputStream(const std::string &path)
    {
        try
        {
            //Create PhysFS stream
            m_ifStream = std::make_unique<PhysFS::ifstream>(path);

            // Read file bytes and store into memory
            char* buffer = new char[m_ifStream->length()];
            m_ifStream->read(buffer, m_ifStream->length());
            if(!m_ifStream->good())
            {
                BF_EXCEPTION("Failed to load resource {}. Failed to open file", path);
            }

            open(buffer, m_ifStream->length());

            //File is opened
            m_isOpened = true;
        }
        catch(const std::exception& err)
        {
            BF_ERROR(err.what());
            m_isOpened = false;
        }
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
}