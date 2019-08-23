#pragma once

#include "trdWindow.hpp"
#include "trdConfig.hpp"
#include "trdSettings.hpp"
#include "trdControlledCamera.hpp"
#include "trColorBuffer.hpp"
#include "trDepthBuffer.hpp"

namespace trd
{
	class App
	{
	public:
		                 App();

		void             mainLoop();

	private:
		void             initWindow();
		void             updateInputs(const float deltaTime);

	private:
		const Config     m_config;
		Settings         m_settings;
		Window           m_window;
		bool             m_running;
		tr::ColorBuffer  m_colorBuffer;
		tr::DepthBuffer  m_depthBuffer;
		ControlledCamera m_camera;
	};
}