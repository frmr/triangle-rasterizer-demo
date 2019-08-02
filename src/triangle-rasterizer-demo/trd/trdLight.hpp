#pragma once

#include "Vectors.h"

namespace trd
{
	class Light
	{
	protected:
		               Light(const Vector3& color);

	public:
		const Vector3& getColor() const;

	private:
		Vector3        m_color;
	};
}