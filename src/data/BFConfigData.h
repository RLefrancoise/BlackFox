#ifndef BLACKFOX_CONFIGDATA_H
#define BLACKFOX_CONFIGDATA_H

#include <memory>
#include <string>
#include <fmt/format.h>
#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

#include "BFIniFile.h"

namespace BlackFox
{
    struct ConfigApplicationData
    {
        std::string name;
        sf::Uint32 frameRate = 60;
        bool fullScreen = false;
        sf::Vector2u windowSize = sf::Vector2u(800, 600);
    };

    class BFConfigData
    {
    public:
        typedef std::shared_ptr<BFConfigData> Ptr;

        explicit BFConfigData(const BFIniFile& file)
        {
            appData = {
                file.get("Application", "name", "BlackFox"), //name
                file.getIntTo<sf::Uint32>("Application", "frameRate", 60), //frame rate
                file.getBool("Application", "fullScreen", false), //full screen
                sf::Vector2u( //window size
                    file.getInt("Application", "width", 800),
                    file.getInt("Application", "height", 600))};
        }

        ConfigApplicationData appData;

        explicit operator std::string() const
        {
            return fmt::format("BFConfigData[name={}, frameRate={}, fullScreen={}, windowSize={},{}]"
                    , appData.name
                    , appData.frameRate
                    , appData.fullScreen
                    , appData.windowSize.x
                    , appData.windowSize.y);
        }
    };
}

#endif //BLACKFOX_CONFIGDATA_H
