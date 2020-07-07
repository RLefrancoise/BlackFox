#include "BFLuaScriptingSFMLEntities.h"
#include "BFColorUtils.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <random>
#include <sol/property.hpp>
#include <sol/raii.hpp>
#include <sol/overload.hpp>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingSFMLEntities, "SFMLEntities")

namespace BlackFox
{
	sf::Color randomColorWithAlpha(const bool randomAlpha)
	{
		const auto seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
		std::minstd_rand0 generator(seed);

		if (randomAlpha) return sf::Color(generator() % 256, generator() % 256, generator() % 256, generator() % 256);
		return sf::Color(generator() % 256, generator() % 256, generator() % 256);
	}

	sf::Color randomColor()
	{
		return randomColorWithAlpha(false);
	}

	void BFLuaScriptingSFMLEntities::registerEntity()
	{
		//Graphics
		auto graphicsNs = m_namespace["Graphics"].get_or_create<sol::table>();

		//Color
		auto color_t = graphicsNs.new_usertype<sf::Color>("Color",
			sol::constructors<
				sf::Color(),
				sf::Color(sf::Uint8, sf::Uint8, sf::Uint8),
				sf::Color(sf::Uint8, sf::Uint8, sf::Uint8, sf::Uint8)>());
		color_t["r"] = &sf::Color::r;
		color_t["g"] = &sf::Color::g;
		color_t["b"] = &sf::Color::b;
		color_t["a"] = &sf::Color::a;

		color_t["Black"] = sol::var(std::ref(sf::Color::Black));				///< Black predefined color
		color_t["White"] = sol::var(std::ref(sf::Color::White));				///< White predefined color
		color_t["Red"] = sol::var(std::ref(sf::Color::Red));					///< Red predefined color
		color_t["Green"] = sol::var(std::ref(sf::Color::Green));				///< Green predefined color
		color_t["Blue"] = sol::var(std::ref(sf::Color::Blue));					///< Blue predefined color
		color_t["Yellow"] = sol::var(std::ref(sf::Color::Yellow));				///< Yellow predefined color
		color_t["Magenta"] = sol::var(std::ref(sf::Color::Magenta));			///< Magenta predefined color
		color_t["Cyan"] = sol::var(std::ref(sf::Color::Cyan));					///< Cyan predefined color
		color_t["Transparent"] = sol::var(std::ref(sf::Color::Transparent));	///< Transparent (black) predefined color

		//Create a random color
		color_t["random"] = sol::overload(&randomColor, &randomColorWithAlpha);

		//Lerp color
		color_t["lerp"] = [](const BFColor& min, const BFColor& max, const float t) -> BFColor
		{
			return Utils::lerp(min, max, t);
		};

		//IntRect
		auto intrect_t = graphicsNs.new_usertype<sf::IntRect>("IntRect", 
			sol::constructors<
				sf::IntRect(), 
				sf::IntRect(int, int, int, int),
				sf::IntRect(sf::Vector2i, sf::Vector2i)>());

		intrect_t["contains"] = sol::overload(
				[&](sf::IntRect& rect, const int x, const int y) {
					return rect.contains(x, y);
				},
				[&](sf::IntRect& rect, const sf::Vector2i& v) {
					return rect.contains(v);
				});

		intrect_t["intersects"] = [&](sf::IntRect& rect, const sf::IntRect& testRect) {
			sf::IntRect intersection;
			return std::make_tuple(rect.intersects(testRect, intersection), intersection);
		};

		intrect_t["left"] = &sf::IntRect::left;
		intrect_t["top"] = &sf::IntRect::top;
		intrect_t["width"] = &sf::IntRect::width;
		intrect_t["height"] = &sf::IntRect::height;

		//FloatRect
		auto floatrect_t = graphicsNs.new_usertype<sf::FloatRect>("FloatRect",
            sol::constructors<
                sf::FloatRect(),
                sf::FloatRect(float, float, float, float),
                sf::FloatRect(sf::Vector2f, sf::Vector2f)>());

		floatrect_t["contains"] = sol::overload(
				[&](sf::FloatRect& rect, const float x, const float y) {
					return rect.contains(x, y);
				},
				[&](sf::FloatRect& rect, const sf::Vector2f& v) {
					return rect.contains(v);
				});

		floatrect_t["intersects"] = [&](sf::FloatRect& rect, const sf::FloatRect& testRect) {
			sf::FloatRect intersection;
			return std::make_tuple(rect.intersects(testRect, intersection), intersection);
		};

		floatrect_t["left"] = &sf::FloatRect::left;
		floatrect_t["top"] = &sf::FloatRect::top;
		floatrect_t["width"] = &sf::FloatRect::width;
		floatrect_t["height"] = &sf::FloatRect::height;
	}
}