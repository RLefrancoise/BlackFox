#include "BFEngineConfig.h"

namespace BlackFox
{
    BFEngineConfig::BFEngineConfig(const BFIniFile& iniFile)
    {
        //App data
        appData = {
                iniFile.get("Application", "name", "BlackFox"), //name
                iniFile.getIntTo<sf::Uint32>("Application", "frameRate", 60), //frame rate
                iniFile.getBool("Application", "fullScreen", false), //full screen
                BFVector2u( //window size
                        iniFile.getIntTo<unsigned int>("Application", "width", 800),
                        iniFile.getIntTo<unsigned int>("Application", "height", 600)),
                iniFile.getBool("Application", "showFrameRate", false), //show frame rate
                iniFile.getIntTo<sf::Uint32>("Application", "antiAliasing", 0) // Anti aliasing
        };

        //Game data
        gameData = {
                iniFile.getFloat("Game", "worldUnitPixels", 32) // world unit pixels
        };

        //Time data
        timeData = {
                iniFile.getFloat("Time", "fixedUpdateInterval", 0.016f) // fixed update interval
        };

        //Physics data
        physicsData = {
                vector2fFromString(iniFile.get("Physics", "gravity", "0.0,-9.81")),
                iniFile.getIntTo<sf::Uint32>("Physics", "velocityIterations", 8),
                iniFile.getIntTo<sf::Uint32>("Physics", "positionIterations", 3),
                iniFile.getFloat("Physics", "physicsScale", 1)
        };

        //Debug data
        debugData = {
                iniFile.getBool("Debug", "debugPhysics", false),
                iniFile.getFloat("Debug", "physicsCollidersOutlineThickness", 0.2f),
                Utils::colorFromString(iniFile.get("Debug", "physicsCollidersOutlineColor", "255,0,0,255")),
                iniFile.getFloat("Debug", "physicsCollidersCenterRadius", 2.f),
                Utils::colorFromString(iniFile.get("Debug", "physicsCollidersCenterColor", "0,0,255,255"))
        };
    }
}