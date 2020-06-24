#pragma once

#include <memory>
#include <string>
#include <fmt/format.h>
#include <SFML/Config.hpp>

#include "BFTypeDefs.h"
#include "BFExport.h"
#include "BFIniFile.h"
#include "BFVector2.h"
#include "BFStringUtils.h"
#include "BFColorUtils.h"

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
        /*! \brief Anti aliasing level */
        sf::Uint32 antiAliasing = 0;

        explicit operator std::string() const
        {
			return fmt::format("--- Application Data ---\nname={}\nframeRate={}\nfullScreen={}\nwindowSize=({},{})\nshowFrameRate={}\nantiAliasing={}\n"
				, name
				, frameRate
				, fullScreen
				, windowSize.x
				, windowSize.y
				, showFrameRate
                , antiAliasing);
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

		[[nodiscard]] constexpr float worldToPixels(const float value) const
        {
		    return value * worldUnitPixels;
        }

        [[nodiscard]] constexpr float pixelsToWorld(const float value) const
        {
		    return value / worldUnitPixels;
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
        sf::Uint32 velocityIterations = 8;

		/// \brief  Position iterations
        sf::Uint32 positionIterations = 3;

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

	/*!
	 * Debug data in config.ini file
	 */
    struct BLACKFOX_EXPORT ConfigDebugData
    {
        /// Debug physics ?
        bool debugPhysics = false;

        /// Thickness of physics colliders outline
        float physicsCollidersOutlineThickness = 2.f;

        /// Color of physics colliders outline
        BFColor physicsCollidersOutlineColor = BFColor::Red;

        /// Radius of physics colliders center
        float physicsCollidersCenterRadius = 2.f;

        /// Color of physics colliders center
        BFColor physicsCollidersCenterColor = BFColor::Blue;

        explicit operator std::string() const
        {
            return fmt::format("--- Debug Data ---\ndebugPhysics={}\nphysicsCollidersOutlineThickness={}\nphysicsCollidersOutlineColor={}\nphysicsColliderCenterRadius={}\nphysicsColliderCenterColor={}\n"
                    , debugPhysics
                    , physicsCollidersOutlineThickness
                    , Utils::colorToString(physicsCollidersOutlineColor)
                    , physicsCollidersCenterRadius
                    , Utils::colorToString(physicsCollidersCenterColor));
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
                    file.getIntTo<unsigned int>("Application", "width", 800),
                    file.getIntTo<unsigned int>("Application", "height", 600)),
                file.getBool("Application", "showFrameRate", false), //show frame rate
                file.getIntTo<sf::Uint32>("Application", "antiAliasing", 0) // Anti aliasing
            };

            //Game data
            gameData = {
                file.getFloat("Game", "worldUnitPixels", 32) // world unit pixels
            };

            //Time data
            timeData = {
                file.getFloat("Time", "fixedUpdateInterval", 0.016f) // fixed update interval
            };

        	//Physics data
            physicsData = {
                vector2fFromString(file.get("Physics", "gravity", "0.0,-9.81")),
				file.getIntTo<sf::Uint32>("Physics", "velocityIterations", 8),
				file.getIntTo<sf::Uint32>("Physics", "positionIterations", 3),
                file.getFloat("Physics", "physicsScale", 1)
            };

            //Debug data
            debugData = {
                file.getBool("Debug", "debugPhysics", false),
                file.getFloat("Debug", "physicsCollidersOutlineThickness", 0.2f),
                Utils::colorFromString(file.get("Debug", "physicsCollidersOutlineColor", "255,0,0,255")),
                file.getFloat("Debug", "physicsCollidersCenterRadius", 2.f),
                Utils::colorFromString(file.get("Debug", "physicsCollidersCenterColor", "0,0,255,255"))
            };
        }
        
        /// Application data
        ConfigApplicationData appData;
        /// Game data
        ConfigGameData gameData;
        /// Time data
        ConfigTimeData timeData;
    	/// Physics data
        ConfigPhysicsData physicsData;
        /// Debug data
        ConfigDebugData debugData;

        explicit operator std::string() const
        {
            return fmt::format("=== BFConfigData ===\n{}\n{}\n{}\n{}\n{}\n"
                , static_cast<std::string>(appData)
                , static_cast<std::string>(gameData)
                , static_cast<std::string>(timeData)
				, static_cast<std::string>(physicsData)
				, static_cast<std::string>(debugData));
        }
    };
}