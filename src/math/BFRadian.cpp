#include "BFRadian.h"
#include "BFDegree.h"
#include "BFMath.h"

namespace BlackFox
{
	BFRadian::BFRadian(const BFDegree& degrees)
	: m_value((BFMath::PI / 180.f) * degrees.value())
	{
	}

	BFRadian& BFRadian::operator=(const BFDegree & degrees)
	{
		m_value = (BFMath::PI / 180.f) * degrees.value();
		return *this;
	}

	BFRadian& BFRadian::operator=(float angle)
	{
		m_value = angle;
		return *this;
	}

	BFRadian::operator BFDegree() const
	{
		return BFDegree(*this);
	}
}