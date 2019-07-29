#include "trdCamera.hpp"

trd::Camera::Camera(const ScreenSize& screenSize, const uint8_t fov, const float near, const float far)
{
	setPerspective(screenSize, fov, near, far);
}

void trd::Camera::setPerspective(const ScreenSize& screenSize, const uint8_t fov, const float near, const float far)
{
	const float aspectRatio = float(screenSize.height) / float(screenSize.width);
	const float width       = near * std::tanf(degreesToRadians(float(fov) / 2.0f));
	const float height      = width * aspectRatio;

	setPerspective(-width, width, -height, height, near, far);
}

void trd::Camera::translate(const Vector3& translation)
{
	m_position += translation;
}

void trd::Camera::rotate(const Vector2& rotation)
{
	m_rotation += rotation;
}

Vector3 trd::Camera::getPosition() const
{
	return m_position;
}

Vector2 trd::Camera::getRotation() const
{
	return m_rotation;
}

Matrix4 trd::Camera::getProjectionViewMatrix() const
{
	Matrix4 viewMatrix;

	viewMatrix.translate(-m_position);
	viewMatrix.rotateY(-m_rotation.y);
	viewMatrix.rotateX(-m_rotation.x);

	return m_projectionMatrix * viewMatrix;
}

void trd::Camera::drawParameters(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const
{
	const std::vector<tf::String> lines = { 
		tf::String("{}, {}, {}", { std::to_string(m_position.x), std::to_string(m_position.y), std::to_string(m_position.z) }),
		tf::String("{}, {}",     { std::to_string(m_rotation.x), std::to_string(m_rotation.y) })
	};

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::TopLeft, screenSize, buffer);
}

void trd::Camera::setPerspective(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	m_projectionMatrix.identity();

	m_projectionMatrix[0]  = (2.0f * near) / (right - left);	
	m_projectionMatrix[5]  = (2.0f * near) / (top - bottom);	
	m_projectionMatrix[8]  = (right + left) / (right - left);	
	m_projectionMatrix[9]  = (top + bottom) / (top - bottom);	
	m_projectionMatrix[10] = -(far + near) / (far - near);	
	m_projectionMatrix[11] = -1.0f;	
	m_projectionMatrix[14] = -(2.0f * far * near) / (far - near);
}

float trd::Camera::degreesToRadians(const float degrees)
{
	constexpr float pi = 3.141592f;

	return degrees / 180.0f * pi;
}