#include "BFDegree.h"
#include "BFRadian.h"
#include "BFMath.h"

namespace BlackFox
{
	BFDegree::BFDegree(float degrees)
	: m_value(degrees)
	{
	}

	BFDegree::BFDegree(const BFRadian & radians)
	: m_value((180.f / BFMath::PI) * radians.value())
	{
	}

	float BFDegree::value() const
	{
		return m_value;
	}

	BFDegree& BFDegree::operator=(const BFRadian & radians)
	{
		m_value = (180.f / BFMath::PI) * radians.value();
		return *this;
	}

    BFDegree &BFDegree::operator=(float angle)
    {
        m_value = angle;
        return *this;
    }

    float BFDegree::operator()()
    {
        return m_value;
    }
}