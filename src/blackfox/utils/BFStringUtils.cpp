#include "BFStringUtils.h"
#include "BFDebug.h"

#include <fmt/format.h>
#include <sstream>
#include <regex>

namespace BlackFox::Utils
{
    BFColor colorFromString(const std::string& str)
    {
        std::smatch match;
        std::regex_match(str, match, std::regex("^([0-9]{1,3}),([0-9]{1,3}),([0-9]{1,3}),([0-9]{1,3})$"));

        if (match.size() != 5)
        {
            BF_EXCEPTION("Failed to initialize BFColor with the given string {}", str);
        }

        unsigned int r, g, b, a;

        std::istringstream iss(fmt::format("{} {} {} {}", match.str(1), match.str(2), match.str(3), match.str(4)));
        iss >> r >> g >> b >> a;

        return BFColor(r, g, b, a);
    }

    std::string colorToString(const BFColor& color)
    {
        return Utils::join(std::vector<sf::Uint8>{
                color.r,
                color.g,
                color.b,
                color.a});
    }
}