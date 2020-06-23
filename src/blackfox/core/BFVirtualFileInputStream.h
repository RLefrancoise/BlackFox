#pragma once

#include <SFML/System/MemoryInputStream.hpp>
#include <physfs.hpp>
#include <memory>

#include "BFExport.h"

namespace BlackFox
{
    /*!
     * Input stream to access virtual file
     */
    class BLACKFOX_EXPORT BFVirtualFileInputStream final: public sf::MemoryInputStream
    {
    public:
        explicit BFVirtualFileInputStream(const std::string& path);
        ~BFVirtualFileInputStream() override = default;

        bool isOpened();
        sf::Int64 read(void* data, sf::Int64 size) override;
        sf::Int64 seek(sf::Int64 position) override;
        sf::Int64 tell() override;
        sf::Int64 getSize() override;

    private:
        std::unique_ptr<PhysFS::ifstream> m_ifStream;
        bool m_isOpened;
    };
}