#pragma once

#include "Matrices.h"
#include "trdScreenSize.hpp"
#include "trColorBuffer.hpp"
#include "trdTextRenderer.hpp"

namespace trd
{
	class Camera : public TextRenderer
	{
	public:
		        Camera(const ScreenSize& screenSize, const float near, const float far);

		void    setPerspective(const ScreenSize& screenSize, const float near, const float far);

		void    translate(const Vector3& translation);
		void    rotate(const Vector2& rotation);

		Vector3 getPosition() const;
		Vector2 getRotation() const;

		Matrix4 getProjectionViewMatrix() const;

		void    drawParameters(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const;

	private:
		void    setPerspective(const float left, const float right, const float bottom, const float top, const float near, const float far);

	private:
		Vector3 m_position;
		Vector2 m_rotation;
		Matrix4 m_projectionMatrix;
	};
}