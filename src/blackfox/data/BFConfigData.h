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
            return fmt::format("--- Time Data ---\nfixedUpdateInterval={}\n"
                , fixedUpdateInterval);
        }
    };

	/**
	 * Physics data in config.ini file
	 */
	struct BLACKFOX_EXPORT ConfigPhysicsData
	{
        /// \brief  Gravity vector
        BFVector2f gravity = BFVector2(0.0f, -9.81f);

		/// \brief  Velocity iterations
        int velocityIterations = 8;

		/// \brief  Position iterations
        int positionIterations = 3;

        float physicsScale = 1;

        explicit operator std::string() const
        {
            return fmt::format("--- Physics Data ---\ngravity={}\nvelocityIterations={}\npositionIterations={}\nphysicsScale={}\n"
                , static_cast<std::string>(gravity)
				, velocityIterations
				, positionIterations
                , physicsScale);
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
                file.getFloat("Game", "worldUnitPixels", 32) // world unit pixels
            };

            //Time data
            timeData = {
                file.getFloat("Time", "fixedUpdateInterval") // fixed update interval
            };

        	//Physics data
            physicsData = {
                vector2fFromString(file.get("Physics", "gravity", "0.0,-9.81")),
				file.getInt("Physics", "velocityIterations", 8),
				file.getInt("Physics", "positionIterations", 3),
                file.getFloat("Physics", "physicsScale") };
        }

        /// \brief  Application data
        ConfigApplicationData appData;
        /// \brief  Game data
        ConfigGameData gameData;
        /// \brief  Time data
        ConfigTimeData timeData;
    	/// \brief  Physics data
        ConfigPhysicsData physicsData;

        explicit operator std::string() const
        {
            return fmt::format("=== BFConfigData ===\n{}\n{}\n{}\n{}\n"
                , static_cast<std::string>(appData)
                , static_cast<std::string>(gameData)
                , static_cast<std::string>(timeData)
				, static_cast<std::string>(physicsData));
        }
    };
}

#endif //BLACKFOX_CONFIGDATA_H
