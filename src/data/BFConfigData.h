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
    /// --------------------------------------------------------------------------------
    /// <summary>
    /// Application data in config.ini file
    /// </summary>
    /// --------------------------------------------------------------------------------
    struct ConfigApplicationData
    {
        /// <summary>Name of the application</summary>
        std::string name;
        /// <summary>Max framerate</summary>
        sf::Uint32 frameRate = 60;
        /// <summary>Is application in full screen ?</summary>
        bool fullScreen = false;
        /// <summary>Window size</summary>
        BFVector2u windowSize = BFVector2u(800, 600);
        /// <summary>Show frame rate in title bar ?</summary>
        bool showFrameRate = false;

        explicit operator std::string() const
        {
			return fmt::format("--- Application Data ---\nname={}\nframeRate={}\nfullScreen={}\nwindowSize=({},{})\nshowFrameRate={}\n"
				, name
				, frameRate
				, fullScreen
				, windowSize.x
				, windowSize.y
				, showFrameRate);
        }
    };

    /// --------------------------------------------------------------------------------
    /// <summary>
    /// Game data in config.ini file
    /// </summary>
    /// --------------------------------------------------------------------------------
    struct ConfigGameData
    {
        /// <summary>How much pixels is a world unit</summary>
        float worldUnitPixels = 32;

		explicit operator std::string() const
		{
			return fmt::format("--- Game Data ---\nworldUnitPixels={}\n"
				, worldUnitPixels);
		}

        /// --------------------------------------------------------------------------------
        /// <summary>
        /// Convert world units to pixels
        /// </summary>
        /// <param name="x">X coordinate in world unit</param>
        /// <param name="y">Y coordinate in world unit</param>
        /// <returns>Position in pixels</returns>
        /// --------------------------------------------------------------------------------
        BFVector2f worldToPixels(const float x, const float y) const
        {
            return BFVector2f(x * worldUnitPixels, y * worldUnitPixels);
        }

        /// --------------------------------------------------------------------------------
        /// <summary>
        /// Convert pixels to world units
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        /// --------------------------------------------------------------------------------
        BFVector2f pixelsToWorld(const float x, const float y) const
        {
            return BFVector2f(x / worldUnitPixels, y / worldUnitPixels);
        }
    };

    /// --------------------------------------------------------------------------------
    /// <summary>
    /// BlackFox config data
    /// </summary>
    /// --------------------------------------------------------------------------------
    class BFConfigData
    {
    public:
        typedef std::shared_ptr<BFConfigData> Ptr;

        explicit BFConfigData(const BFIniFile& file)
        {
            //App data
            appData = {
                file.get("Application", "name", "BlackFox"), //name
                file.getIntTo<sf::Uint32>("Application", "frameRate", 60), //frame rate
                file.getBool("Application", "fullScreen", false), //full screen
                BFVector2u( //window size
                    file.getInt("Application", "width", 800),
                    file.getInt("Application", "height", 600)),
                file.getBool("Application", "showFrameRate", false) //show frame rate
            };

            //Game data
            gameData = {
                file.getFloat("Game", "worldUnitPixels", 32) // world unit pixels
            };
        }

        /// <summary>Application data</summary>
        ConfigApplicationData appData;
        /// <summary>Game data</summary>
        ConfigGameData gameData;

        explicit operator std::string() const
        {
            return fmt::format("=== BFConfigData ===\n{}\n{}\n"
                , static_cast<std::string>(appData)
                , static_cast<std::string>(gameData));
        }
    };
}

#endif //BLACKFOX_CONFIGDATA_H
