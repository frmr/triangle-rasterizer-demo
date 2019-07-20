#include "trdControlledCamera.hpp"

trd::ControlledCamera::ControlledCamera(const ScreenSize& screenSize, const float near, const float far) :
	Camera(screenSize, near, far)
{
}

void trd::ControlledCamera::update(const InputState& inputState)
{
	constexpr float  translationIncrement = 0.1f;
	constexpr float  mouseSensitivity     = 1.0f;

	if (inputState.getKeyState(Key::MoveForward ).held) { translate(Vector3(0.0f,                   0.0f,                 -translationIncrement)); }
	if (inputState.getKeyState(Key::MoveBackward).held) { translate(Vector3(0.0f,                   0.0f,                  translationIncrement)); }
	if (inputState.getKeyState(Key::MoveLeft    ).held) { translate(Vector3(-translationIncrement,  0.0f,                  0.0f                )); }
	if (inputState.getKeyState(Key::MoveRight   ).held) { translate(Vector3( translationIncrement,  0.0f,                  0.0f                )); }
	if (inputState.getKeyState(Key::MoveUp      ).held) { translate(Vector3(0.0f,                   translationIncrement,  0.0f                )); }
	if (inputState.getKeyState(Key::MoveDown    ).held) { translate(Vector3(0.0f,                  -translationIncrement,  0.0f                )); }

	m_rotation.x -= inputState.getMouseChangeY() * mouseSensitivity;
	m_rotation.y -= inputState.getMouseChangeX() * mouseSensitivity;
}
