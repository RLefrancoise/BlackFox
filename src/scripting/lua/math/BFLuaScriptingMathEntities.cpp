#include "BFLuaScriptingMathEntities.h"
#include "BFDegree.h"
#include "BFRadian.h"
#include "BFVector2.h"

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingMathEntities, "MathEntities")

namespace BlackFox
{
    void BFLuaScriptingMathEntities::registerEntity()
    {
        sol::table math_ns = m_namespace["Math"].get_or_create<sol::table>();

        //Degree
        sol::usertype<BFDegree> degree_t = math_ns.new_usertype<BFDegree>("Degree",
                sol::constructors<BFDegree(float), BFDegree(const BFRadian&)>());
        degree_t["value"] = sol::readonly(&BFDegree::value);

        //Radian
        sol::usertype<BFRadian> radian_t = math_ns.new_usertype<BFRadian>("Radian",
                sol::constructors<BFRadian(float), BFRadian(const BFDegree&)>());
        radian_t["value"] = sol::readonly(&BFRadian::value);

        //Vector2 float
        sol::usertype<BFVector2f> vector2f_t = math_ns.new_usertype<BFVector2f>("Vector2f",
                sol::constructors<BFVector2f(float, float), BFVector2f(const BFVector2f&)>());
        vector2f_t["x"] = &BFVector2f::x;
        vector2f_t["y"] = &BFVector2f::y;

        //Vector2 int
        sol::usertype<BFVector2i> vector2i_t = math_ns.new_usertype<BFVector2i>("Vector2i",
                sol::constructors<BFVector2i(int, int), BFVector2i(const BFVector2i&)>());
        vector2i_t["x"] = &BFVector2i::x;
        vector2i_t["y"] = &BFVector2i::y;
    }
}