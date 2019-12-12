#ifndef BLACKFOX_APPLICATIONDATA_H
#define BLACKFOX_APPLICATIONDATA_H

#include <memory>
#include <string>
#include <cpp-sdl2/vec2.hpp>
#include <fmt/format.h>

#include "BFIniFile.h"

namespace BlackFox
{
    struct ConfigApplicationData
    {
        std::string name;
        Uint32 frameRate = 60;
        bool fullScreen = false;
        sdl::Vec2i windowSize = sdl::Vec2i(800, 600);
    };

    class BFConfigData
    {
    public:
        typedef std::shared_ptr<BFConfigData> Ptr;

        explicit BFConfigData(const BFIniFile& file)
        {
            appData = {
                file.get("Application", "name", "BlackFox"), //name
                file.getIntTo<Uint32>("Application", "frameRate", 60), //frame rate
                file.getBool("Application", "fullScreen", false), //full screen
                sdl::Vec2i( //window size
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

#endif //BLACKFOX_APPLICATIONDATA_H
