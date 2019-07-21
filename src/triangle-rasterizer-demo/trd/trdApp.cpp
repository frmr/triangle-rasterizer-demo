#include "trdApp.hpp"
#include "trdInstructions.hpp"
#include "trdFrameTimer.hpp"
#include "trdRenderManager.hpp"
#include <thread>

trd::App::App() :
	m_settings(),
	m_window(),
	m_running(false),
	m_colorBuffer(),
	m_depthBuffer(),
	m_camera(m_settings.getScreenSize(), 1.0f, 100.0f)
{
	initWindow();
	m_running = true;
}

void trd::App::initWindow()
{
	m_window.init(m_settings.getScreenSize(), m_settings.getFullscreen());
	m_camera.setPerspective(m_settings.getScreenSize(), 1.0f, 100.0f);

	m_colorBuffer = tr::ColorBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
	m_depthBuffer = tr::DepthBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
}

void trd::App::updateInputs(const float deltaTime)
{
	const InputState inputState = m_window.getInputState();
	bool             reinitWindow;

	if (inputState.getKeyState(Key::Quit).pressed || inputState.getQuit())
	{
		m_running = false;
	}

	m_camera.update(inputState, deltaTime);
	m_settings.update(inputState, reinitWindow);

	if (reinitWindow)
	{
		initWindow();
	}
}

void trd::App::mainLoop()
{
	Instructions instructions;
	FrameTimer   frameTimer;

	m_camera.translate(Vector3(0.0f, 0.0f, 4.0f));

	Scene         scene;
	RenderManager renderManager(m_settings, scene);

	while (m_running)
	{
		frameTimer.update();
		updateInputs(frameTimer.getDeltaTime());
		renderManager.draw(m_camera, m_colorBuffer, m_depthBuffer);

		if (m_settings.getInstructionsEnabled())
		{
			instructions.draw(m_settings, m_colorBuffer);
		}
		
		if (m_settings.getFrameRateEnabled())
		{
			frameTimer.draw(m_settings.getScreenSize(), m_colorBuffer);
		}

		m_camera.drawParameters(m_settings.getScreenSize(), m_colorBuffer);
		m_window.copyAndRender(m_colorBuffer);
	}
}
