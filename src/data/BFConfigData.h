#ifndef BLACKFOX_CONFIGDATA_H
#define BLACKFOX_CONFIGDATA_H

#include <memory>
#include <string>
#include <fmt/format.h>
#include <SFML/Config.hpp>

#include "BFIniFile.h"
#include "BFVector2.h"

namespace BlackFox
{
    struct ConfigApplicationData
    {
        std::string name;
        sf::Uint32 frameRate = 60;
        bool fullScreen = false;
        BFVector2u windowSize = BFVector2u(800, 600);
        bool showFrameRate = false;
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
                BFVector2u( //window size
                    file.getInt("Application", "width", 800),
                    file.getInt("Application", "height", 600)),
                file.getBool("Application", "showFrameRate", false) //show frame rate
            };
        }

        ConfigApplicationData appData;

        explicit operator std::string() const
        {
            return fmt::format("BFConfigData[name={}, frameRate={}, fullScreen={}, windowSize=({},{}), showFrameRate={}]"
                    , appData.name
                    , appData.frameRate
                    , appData.fullScreen
                    , appData.windowSize.x
                    , appData.windowSize.y
                    , appData.showFrameRate);
        }
    };
}

#endif //BLACKFOX_CONFIGDATA_H
