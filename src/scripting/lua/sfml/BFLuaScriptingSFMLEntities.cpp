#include "BFLuaScriptingSFMLEntities.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <random>

BF_SCRIPTING_LUA_ENTITY_REGISTER(BlackFox::BFLuaScriptingSFMLEntities, "SFMLEntities")

namespace BlackFox
{
	sf::Color randomColorWithAlpha(bool randomAlpha)
	{
		unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
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

		//IntRect
		auto intrect_t = graphicsNs.new_usertype<sf::IntRect>("IntRect", 
			sol::constructors<
				sf::IntRect(), 
				sf::IntRect(int, int, int, int),
				sf::IntRect(sf::Vector2i, sf::Vector2i)>());

		//FloatRect
		auto floatrect_t = graphicsNs.new_usertype<sf::FloatRect>("FloatRect");
	}
}