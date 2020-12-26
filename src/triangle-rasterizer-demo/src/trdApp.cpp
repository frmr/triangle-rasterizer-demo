#include "trdApp.hpp"
#include "trdInstructions.hpp"
#include "trdFrameTimer.hpp"
#include "trdRenderManager.hpp"
#include "tfTime.hpp"
#include <thread>
#include "lodepng.h"

trd::App::App() :
	m_config(),
	m_settings(m_config.getCustomScreenSize(), m_config.getCustomTileSize()),
	m_window(),
	m_running(false),
	m_colorBuffer(),
	m_depthBuffer(),
	m_camera(m_settings.getScreenSize(), m_settings.getFov()),
	m_lastScreenshotTimestamp(0),
	m_screenshotCount(0)
{
	initWindow();
	m_running = true;
}

void trd::App::initWindow()
{
	m_window.init(m_settings.getScreenSize(), m_settings.getFullscreen());
	m_camera.setPerspective(m_settings.getScreenSize(), m_settings.getFov());

	m_colorBuffer = tr::ColorBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
	m_depthBuffer = tr::DepthBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
}

void trd::App::updateInputs(const float deltaTime, bool& updateTiler)
{
	const InputState inputState = m_window.getInputState();
	bool             reinitWindow;
	bool             reinitCamera;

	if (inputState.getKeyState(Key::Quit).pressed || inputState.getQuit())
	{
		m_running = false;
	}

	m_settings.update(inputState, reinitWindow, reinitCamera, updateTiler);
	m_camera.update(inputState, m_config.getMouseSensitivity(), deltaTime);

	if (reinitWindow)
	{
		initWindow();
		m_window.flushEvents();
	}

	if (reinitCamera)
	{
		m_camera.setPerspective(m_settings.getScreenSize(), m_settings.getFov());
	}
}

void trd::App::saveColorBufferToFile()
{
	const int64_t   currentTimestamp = tf::Time().getTimestamp();
	tr::ColorBuffer rgbaBuffer       = m_colorBuffer;

	// Flip red and blue channels for PNG
	for (size_t x = 0; x < rgbaBuffer.getWidth(); ++x)
	{
		for (size_t y = 0; y < rgbaBuffer.getHeight(); ++y)
		{
			tr::Color& pixel = rgbaBuffer.at(x, y);

			uint8_t r = pixel.r;

			pixel.r = pixel.b;
			pixel.b = r;
		}
	}

	if (currentTimestamp == m_lastScreenshotTimestamp)
	{
		++m_screenshotCount;
	}
	else
	{
		m_screenshotCount         = 0;
		m_lastScreenshotTimestamp = currentTimestamp;
	}

	const tf::String filename("trd_{}_{}.png", { std::to_string(currentTimestamp), std::to_string(m_screenshotCount) });

	lodepng::encode(filename, (unsigned char*)(&rgbaBuffer.getData()->b), (unsigned int)m_settings.getScreenSize().width, (unsigned int)m_settings.getScreenSize().height);
}

void trd::App::mainLoop()
{
	Instructions  instructions;
	FrameTimer    frameTimer;
	Scene         scene;
	RenderManager renderManager(m_settings, scene);

	m_camera.translate(Vector3(0.0f, 6.0f, 10.0f));

	while (m_running)
	{
		bool updateTiler;

		frameTimer.update();
		updateInputs(frameTimer.getDeltaTime(), updateTiler);

		if (updateTiler)
		{
			renderManager.updateTilerAttributes();
		}

		scene.update(m_camera.getPosition(), m_settings.getPauseAnimation(), frameTimer.getFrameTime(), frameTimer.getDeltaTime());
		renderManager.draw(m_camera, m_colorBuffer, m_depthBuffer);

		if (m_settings.getTakeScreenshot())
		{
			saveColorBufferToFile();
			m_settings.resetTakeScreenshot();
		}

		if (m_settings.getInstructionsEnabled())
		{
			instructions.draw(m_settings, m_colorBuffer);
		}
		
		if (m_settings.getFrameRateEnabled())
		{
			frameTimer.draw(m_settings.getScreenSize(), m_colorBuffer);
		}

		m_window.copyAndRender(m_colorBuffer);
	}
}
