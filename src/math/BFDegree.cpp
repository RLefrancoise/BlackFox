#include "BFDegree.h"
#include "BFRadian.h"
#include "BFMath.h"

namespace BlackFox
{
	BFDegree::BFDegree(const BFRadian& radians)
	: m_value((180.f / BFMath::PI) * radians.value())
	{
	}

	BFDegree& BFDegree::operator=(const BFRadian & radians)
	{
		m_value = (180.f / BFMath::PI) * radians.value();
		return *this;
	}
}