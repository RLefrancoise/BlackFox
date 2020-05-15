#ifndef BLACKFOX_CONFIGDATA_H
#define BLACKFOX_CONFIGDATA_H

#include <memory>
#include <string>
#include <fmt/format.h>
#include <SFML/Config.hpp>

#include "BFTypeDefs.h"
#include "BFIniFile.h"
#include "BFVector2.h"

namespace BlackFox
{
    /// --------------------------------------------------------------------------------
    /// <summary>
    /// Application data in config.ini file
    /// </summary>
    /// --------------------------------------------------------------------------------
    struct BLACKFOX_EXPORT ConfigApplicationData
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

    /// \brief  Game data in config.ini file
    struct BLACKFOX_EXPORT ConfigGameData
    {
        /// \brief  How much pixels is a world unit
        float worldUnitPixels = 32;

    	/// \brief  Gravity vector
        BFVector2f gravity = BFVector2(0.0f, -9.81f);

		explicit operator std::string() const
		{
			return fmt::format("--- Game Data ---\nworldUnitPixels={}\ngravity={}\n"
				, worldUnitPixels, static_cast<std::string>(gravity));
		}

        /// --------------------------------------------------------------------------------
        /// <summary>
        /// Convert world units to pixels
        /// </summary>
        /// <param name="x">X coordinate in world unit</param>
        /// <param name="y">Y coordinate in world unit</param>
        /// <returns>Position in pixels</returns>
        /// --------------------------------------------------------------------------------
        [[nodiscard]] BFVector2f worldToPixels(const float x, const float y) const
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
        [[nodiscard]] BFVector2f pixelsToWorld(const float x, const float y) const
        {
            return BFVector2f(x / worldUnitPixels, y / worldUnitPixels);
        }
    };

    /// --------------------------------------------------------------------------------
    /// <summary>
    /// Time Data in config.ini file
    /// </summary>
    /// --------------------------------------------------------------------------------
    struct BLACKFOX_EXPORT ConfigTimeData
    {
        /// <summary>Fixed update interval in seconds</summary>
        float fixedUpdateInterval = 0.1f;

        explicit operator std::string() const
        {
            return fmt::format("--- Physics Data ---\nfixedUpdateInterval={}"
                , fixedUpdateInterval);
        }
    };

    /// --------------------------------------------------------------------------------
    /// <summary>
    /// BlackFox config data
    /// </summary>
    /// --------------------------------------------------------------------------------
    class BLACKFOX_EXPORT BFConfigData
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
                file.getFloat("Game", "worldUnitPixels", 32), // world unit pixels
            	vector2fFromString(file.get("Game", "gravity", "0.0,-9.81"))
            };

            //Physics data
            timeData = {
                file.getFloat("Time", "fixedUpdateInterval") // fixed update interval
            };
        }

        /// <summary>Application data</summary>
        ConfigApplicationData appData;
        /// <summary>Game data</summary>
        ConfigGameData gameData;
        /// <summary>Time data</summary>
        ConfigTimeData timeData;

        explicit operator std::string() const
        {
            return fmt::format("=== BFConfigData ===\n{}\n{}\n{}\n"
                , static_cast<std::string>(appData)
                , static_cast<std::string>(gameData)
                , static_cast<std::string>(timeData));
        }
    };
}

#endif //BLACKFOX_CONFIGDATA_H
