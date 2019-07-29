#pragma once

#include "trdCamera.hpp"
#include "trdInputState.hpp"

namespace trd
{
	class ControlledCamera : public Camera
	{
	public:
		                       ControlledCamera(const ScreenSize& screenSize, const uint8_t fov);

		void                   setPerspective(const ScreenSize& screenSize, const uint8_t fov);
		void                   update(const InputState& inputState, const float deltaTime);

	private:
		static constexpr float s_near = 0.1f;
		static constexpr float s_far  = 100.0f;
	};
}