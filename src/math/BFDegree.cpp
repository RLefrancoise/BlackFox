#include "BFDegree.h"
#include "BFRadian.h"
#include "BFMath.h"

BlackFox::BFDegree::BFDegree(float degrees) : m_value(degrees)
{
}

BlackFox::BFDegree::BFDegree(const BFRadian & radians) : m_value( (180.f / BFMath::PI) * radians.value())
{
}

float BlackFox::BFDegree::value() const
{
	return m_value;
}

BlackFox::BFDegree BlackFox::BFDegree::operator=(const BFRadian & radians) const
{
	return BFDegree(radians);
}
