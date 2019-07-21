#pragma once

#include "trdCamera.hpp"
#include "trdInputState.hpp"

namespace trd
{
	class ControlledCamera : public Camera
	{
	public:
		             ControlledCamera(const ScreenSize& screenSize, const float near, const float far);

		void         update(const InputState& inputState, const float deltaTime);

	private:
		static float degreesToRadians(const float degrees);
	};
}