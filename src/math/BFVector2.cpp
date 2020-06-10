#include "BFVector2.h"
#include "BFDebug.h"

namespace BlackFox
{
	BFVector2f vector2fFromString(const std::string& str)
	{
		std::smatch match;
		std::regex_match(str, match, std::regex("^(-?[0-9]*\\.{0,1}[0-9]+),(-?[0-9]*\\.{0,1}[0-9]+)$"));

		if (match.size() != 3)
		{
			BF_EXCEPTION("Failed to initialize BFVector2 with the given string {}", str);
		}

		BFVector2f v;

		std::istringstream xIss(match.str(1));
		xIss >> v.x;
		std::istringstream yIss(match.str(2));
		yIss >> v.y;

		return v;
	}
}
