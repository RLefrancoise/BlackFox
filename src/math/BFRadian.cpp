#include "BFRadian.h"
#include "BFDegree.h"
#include "BFMath.h"

namespace BlackFox
{
	BFRadian::BFRadian(float radians)
	: m_value(radians)
	{
	}

	BFRadian::BFRadian(const BFDegree & degrees)
	: m_value((BFMath::PI / 180.f) * degrees.value())
	{
	}

	float BFRadian::value() const
	{
		return m_value;
	}

	BFRadian& BFRadian::operator=(const BFDegree & degrees)
	{
		m_value = (BFMath::PI / 180.f) * degrees.value();
		return *this;
	}
}