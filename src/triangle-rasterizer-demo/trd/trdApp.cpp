#include "trdApp.hpp"
#include "trdExternalLibraryException.hpp"
#include "trdInstructions.hpp"
#include "trdFrameRateCounter.hpp"
#include "trdMeshMap.hpp"
#include "trdModel.hpp"
#include "trdRenderManager.hpp"
#include <thread>

trd::App::App() :
	m_reinitWindow(false),
	m_running(false),
	m_sdlWindow(nullptr),
	m_sdlRenderer(nullptr),
	m_sdlTexture(nullptr),
	m_camera(m_settings.getScreenSize(), 1.0f, 100.0f)
{
	initSdl();
	initWindow();

	m_running = true;
}

trd::App::~App()
{
	deinitWindow();
	SDL_Quit();
}

void trd::App::initSdl()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		throw ExternalLibraryException("trd::App::initSdl(): Failed to initialise SDL");
	}
}

void trd::App::initWindow()
{
	deinitWindow();

	m_sdlWindow = SDL_CreateWindow("Triangle rasterizer demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(m_settings.getScreenSize().width), int(m_settings.getScreenSize().height), SDL_WINDOW_SHOWN | (m_settings.getFullscreen() ? SDL_WINDOW_FULLSCREEN : 0));

	if (!m_sdlWindow)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL window");
	}

	m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!m_sdlRenderer)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialise SDL renderer");
	}

	m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, int(m_settings.getScreenSize().width), int(m_settings.getScreenSize().height));

	if (!m_sdlTexture)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL teuxtre");
	}

	m_colorBuffer = tr::ColorBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
	m_depthBuffer = tr::DepthBuffer(m_settings.getScreenSize().width, m_settings.getScreenSize().height);
	m_camera.setPerspective(m_settings.getScreenSize(), 1.0f, 100.0f);
}

void trd::App::deinitWindow()
{
	SDL_DestroyTexture(m_sdlTexture);
	SDL_DestroyRenderer(m_sdlRenderer);
	SDL_DestroyWindow(m_sdlWindow);
}

void trd::App::updateInputs()
{
	SDL_Event event;

 	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			m_running = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			constexpr float translationIncrement = 0.1f;
			constexpr float rotationIncrement    = 2.0f;

 			if      (event.key.keysym.sym == SDLK_ESCAPE) { m_running = false;                                              }
			else if (event.key.keysym.sym == SDLK_1)      { m_settings.cycleScreenSize();  m_reinitWindow = true;           }
			else if (event.key.keysym.sym == SDLK_2)      { m_settings.toggleFullscreen(); m_reinitWindow = true;           }
			else if (event.key.keysym.sym == SDLK_3)      { m_settings.cycleNumThreads();                                   }
			else if (event.key.keysym.sym == SDLK_5)      { m_settings.cycleRenderMode();                                   }
			else if (event.key.keysym.sym == SDLK_6)      { m_settings.cycleTextureMode();                                  }
			else if (event.key.keysym.sym == SDLK_8)      { m_settings.toggleInstructionsEnabled();                         }
			else if (event.key.keysym.sym == SDLK_9)      { m_settings.toggleFrameRateEnabled();                            }
			else if (event.key.keysym.sym == SDLK_w)      { m_camera.translate(Vector3(0.0f, 0.0f, -translationIncrement)); }
			else if (event.key.keysym.sym == SDLK_a)      { m_camera.translate(Vector3(-translationIncrement, 0.0f, 0.0f)); }
			else if (event.key.keysym.sym == SDLK_s)      { m_camera.translate(Vector3(0.0f, 0.0f, translationIncrement));  }
			else if (event.key.keysym.sym == SDLK_d)      { m_camera.translate(Vector3(translationIncrement, 0.0f, 0.0f));  }
			else if (event.key.keysym.sym == SDLK_SPACE)  { m_camera.translate(Vector3(0.0f, translationIncrement, 0.0f));  }
			else if (event.key.keysym.sym == SDLK_LCTRL)  { m_camera.translate(Vector3(0.0f, -translationIncrement, 0.0f)); }
			else if (event.key.keysym.sym == SDLK_LEFT)   { m_camera.rotate(Vector2(0.0f, rotationIncrement));              }
			else if (event.key.keysym.sym == SDLK_RIGHT)  { m_camera.rotate(Vector2(0.0f, -rotationIncrement));             }
			else if (event.key.keysym.sym == SDLK_UP)     { m_camera.rotate(Vector2(rotationIncrement, 0.0f));              }
			else if (event.key.keysym.sym == SDLK_DOWN)   { m_camera.rotate(Vector2(-rotationIncrement, 0.0f));             }
		}
	}
}

void trd::App::renderColorBufferToWindow()
{
	tr::Color* pixels;
	int        pitch;

 	SDL_SetRenderTarget(m_sdlRenderer, m_sdlTexture);
	SDL_LockTexture(m_sdlTexture, NULL, (void**)&pixels, &pitch);

 	memcpy(pixels, m_colorBuffer.getData(), m_colorBuffer.getWidth() * m_colorBuffer.getHeight() * 4);

 	SDL_UnlockTexture(m_sdlTexture);
	SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, NULL);
	SDL_RenderPresent(m_sdlRenderer);
}

void trd::App::mainLoop()
{
	Instructions     instructions;
	FrameRateCounter frameRateCounter;

	m_camera.translate(Vector3(0.0f, 0.0f, 4.0f));

	Scene         scene;
	RenderManager renderManager(m_settings, scene);

	while (m_running)
	{
		updateInputs();

		if (m_reinitWindow)
		{
			initWindow();
			m_reinitWindow = false;
		}

		m_colorBuffer.fill(tr::Color(0, 0, 0, 255));
		m_depthBuffer.fill(1.0f);

		renderManager.draw(m_camera, m_colorBuffer, m_depthBuffer);

		if (m_settings.getInstructionsEnabled())
		{
			instructions.draw(m_settings, m_colorBuffer);
		}
		
		if (m_settings.getFrameRateEnabled())
		{
			frameRateCounter.draw(m_settings.getScreenSize(), m_colorBuffer);
		}

		m_camera.drawParameters(m_settings.getScreenSize(), m_colorBuffer);

		renderColorBufferToWindow();

		frameRateCounter.update();
	}
}
