#include "BFRadian.h"
#include "BFDegree.h"
#include "BFMath.h"

BlackFox::BFRadian::BFRadian(float radians) : m_value(radians)
{
}

BlackFox::BFRadian::BFRadian(const BFDegree & degrees) : m_value( (BFMath::PI / 180.f) * degrees.value())
{
}

float BlackFox::BFRadian::value() const
{
	return m_value;
}

BlackFox::BFRadian BlackFox::BFRadian::operator=(const BFDegree & degrees) const
{
	return BFRadian(degrees);
}
