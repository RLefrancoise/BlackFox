#include "BFLuaScriptingMathEntities.h"
#include "BFDegree.h"
#include "BFRadian.h"
#include "BFVector2.h"
#include "BFMath.h"

#include <sol/property.hpp>
#include <sol/raii.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingMathEntities, "MathEntities")

namespace BlackFox
{
    void BFLuaScriptingMathEntities::registerEntity()
    {
        sol::table math_ns = m_namespace["Math"].get_or_create<sol::table>();

        //Degree
        auto degree_t = math_ns.new_usertype<BFDegree>("Degree", sol::constructors<BFDegree(float), BFDegree(const BFRadian&)>());
        degree_t["value"] = sol::property(
                [](BFDegree& degree)
                {
                    return degree.value();
                },
                [](BFDegree& degree, const float value)
                {
                    degree = value;
                });
        degree_t["degrees"] = sol::property([](BFDegree& degree) { return degree; }, [&](BFDegree& degree, const float degrees) { degree = degrees; });
        degree_t["radians"] = sol::property([](BFDegree& degree) { return BFRadian(degree); }, [&](BFDegree& degree, const float radians) { degree = BFRadian(radians); });

        //Radian
        auto radian_t = math_ns.new_usertype<BFRadian>("Radian", sol::constructors<BFRadian(float), BFRadian(const BFDegree&)>());
        radian_t["value"] = sol::property(
                [](BFRadian& radian)
                {
                    return radian.value();
                },
                [](BFRadian& radian, const float value)
                {
                    radian = value;
                });
		radian_t["radians"] = sol::property([](BFRadian& radian) { return radian; }, [&](BFRadian& radian, const float radians) { radian = radians; });
		radian_t["degrees"] = sol::property([](BFRadian& radian) { return BFDegree(radian); }, [&](BFRadian& radian, const float degrees) { radian = BFDegree(degrees); });

        //Vector2 float
        auto vector2f_t = math_ns.new_usertype<BFVector2f>("Vector2f", sol::constructors<BFVector2f(float, float), BFVector2f(const BFVector2f&)>());
        vector2f_t["x"] = &BFVector2f::x;
        vector2f_t["y"] = &BFVector2f::y;

        //Vector2 int
        auto vector2i_t = math_ns.new_usertype<BFVector2i>("Vector2i", sol::constructors<BFVector2i(int, int), BFVector2i(const BFVector2i&)>());
        vector2i_t["x"] = &BFVector2i::x;
        vector2i_t["y"] = &BFVector2i::y;

        // Various functions

        // Get direction vector from angle
        math_ns["direction"] = sol::overload(
                [](const BFRadian& rad) { return BFMath::direction(rad); },
                [](const BFDegree& deg) { return BFMath::direction(deg); },
                [](const float deg) { return BFMath::direction(BFDegree(deg)); });

        // Lerp float
        math_ns["lerp"] = [](const float min, const float max, const float t)
        {
            return BFMath::lerp<float>(min, max, t);
        };

        //Clamp float
        math_ns["clamp"] = [](const float value, const float min, const float max)
        {
            return BFMath::clamp<float>(value, min, max);
        };
    }
}