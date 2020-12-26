#pragma once

#include "Vectors.h"
#include "trQuadVec3.hpp"

namespace trd
{
	class Light
	{
	protected:
		                    Light(const Vector3& color);

	public:
		const tr::QuadVec3& getColor() const;

	private:
		tr::QuadVec3        m_color;
	};
}