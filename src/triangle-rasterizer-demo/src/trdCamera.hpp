#pragma once

#include "Matrices.h"
#include "trdScreenSize.hpp"
#include "trColorBuffer.hpp"

namespace trd
{
	class Camera
	{
	public:
		             Camera(const ScreenSize& screenSize, const uint8_t fov, const float near, const float far);

		void         setPerspective(const ScreenSize& screenSize, const uint8_t fov, const float near, const float far);

		void         translate(const Vector3& translation);
		void         rotate(const Vector2& rotation);

		Vector3      getPosition() const;
		Vector2      getRotation() const;

		Matrix4      getProjectionViewMatrix() const;

	protected:
		void         setPerspective(const float left, const float right, const float bottom, const float top, const float near, const float far);
		static float degreesToRadians(const float degrees);

	protected:
		Vector3      m_position;
		Vector2      m_rotation;
		Matrix4      m_projectionMatrix;
	};
}