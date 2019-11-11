#include "BFVector2.h"

namespace BlackFox
{
	BFVector2::BFVector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	BFVector2 BFVector2::operator+(const BFVector2 & rhs) const
	{
		return BFVector2(x + rhs.x, y + rhs.y);
	}

	BFVector2 BFVector2::operator-(const BFVector2 & rhs) const
	{
		return BFVector2(x - rhs.x, y - rhs.y);
	}

	BFVector2 BFVector2::operator-(void) const
	{
		return BFVector2(-x, -y);
	}

	BFVector2 BFVector2::operator*(float scale) const
	{
		return BFVector2(x * scale, y * scale);
	}

	BFVector2 & BFVector2::operator+(const BFVector2 & rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	BFVector2 & BFVector2::operator-(const BFVector2 & rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	BFVector2 & BFVector2::operator-(void)
	{
		x = -x;
		y = -y;
		return *this;
	}

	BFVector2 & BFVector2::operator*(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	bool BFVector2::operator==(const BFVector2 & rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool BFVector2::operator!=(const BFVector2 & rhs) const
	{
		return !(*this == rhs);
	}
}