#include "trdControlledCamera.hpp"

trd::ControlledCamera::ControlledCamera(const ScreenSize& screenSize, const float near, const float far) :
	Camera(screenSize, near, far)
{
}

void trd::ControlledCamera::update(const InputState& inputState)
{
	constexpr float  movementSpeed    = 0.01f;
	constexpr float  mouseSensitivity = 1.0f;

	m_rotation.x -= inputState.getMouseChangeY() * mouseSensitivity;
	m_rotation.y -= inputState.getMouseChangeX() * mouseSensitivity;

	m_rotation.x = std::clamp(m_rotation.x, -90.0f, 90.0f);

	Vector3 forwardVector(
		std::sin(degreesToRadians( m_rotation.y)),
		std::tan(degreesToRadians(-m_rotation.x)),
		std::cos(degreesToRadians( m_rotation.y))
	);

	Vector3 rightVector(forwardVector.z, 0.0f, -forwardVector.x);
	Vector3 upVector(0.0f, 1.0f, 0.0f);

	forwardVector.normalize();
	rightVector.normalize();

	Vector3 movementVector;

	if (inputState.getKeyState(Key::MoveForward ).held) { movementVector -= forwardVector; }
	if (inputState.getKeyState(Key::MoveBackward).held) { movementVector += forwardVector; }
	if (inputState.getKeyState(Key::MoveLeft    ).held) { movementVector -= rightVector; }
	if (inputState.getKeyState(Key::MoveRight   ).held) { movementVector += rightVector; }
	if (inputState.getKeyState(Key::MoveUp      ).held) { movementVector += upVector; }
	if (inputState.getKeyState(Key::MoveDown    ).held) { movementVector -= upVector; }

	if (movementVector.length() > 0.0f)
	{
		translate(movementVector.normalize() * movementSpeed);
	}
}

float trd::ControlledCamera::degreesToRadians(const float degrees)
{
	constexpr float pi = 3.141592f;

	return degrees / 180.0f * pi;
}
