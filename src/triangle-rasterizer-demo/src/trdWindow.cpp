#include "trdWindow.hpp"
#include "trdExternalLibraryException.hpp"
#include "trColor.hpp"
#include <map>
#include <cstring>

trd::Window::Window() :
	m_sdlWindow(nullptr),
	m_sdlRenderer(nullptr),
	m_sdlTexture(nullptr),
	m_inputState()
{
	initSdl();
}

trd::Window::~Window()
{
	destroy();
	SDL_Quit();
}

void trd::Window::init(const ScreenSize& screenSize, const bool fullscreen)
{
	destroy();

	m_sdlWindow = SDL_CreateWindow("Triangle rasterizer demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, int(screenSize.width), int(screenSize.height), SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_GRABBED | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));

	if (!m_sdlWindow)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL window");
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	m_sdlRenderer = SDL_CreateRenderer(m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!m_sdlRenderer)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialise SDL renderer");
	}

	m_sdlTexture = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, int(screenSize.width), int(screenSize.height));

	if (!m_sdlTexture)
	{
		throw ExternalLibraryException("trd::App::initWindow(): Failed to initialize SDL teuxtre");
	}
}

void trd::Window::copyAndRender(tr::ColorBuffer& colorBuffer)
{
	tr::Color* pixels;
	int        pitch;

 	SDL_SetRenderTarget(m_sdlRenderer, m_sdlTexture);
	SDL_LockTexture(m_sdlTexture, NULL, (void**)&pixels, &pitch);

 	std::memcpy(pixels, colorBuffer.getData(), colorBuffer.getWidth() * colorBuffer.getHeight() * 4);

 	SDL_UnlockTexture(m_sdlTexture);
	SDL_RenderCopy(m_sdlRenderer, m_sdlTexture, NULL, NULL);
	SDL_RenderPresent(m_sdlRenderer);
}

trd::InputState trd::Window::getInputState()
{
	if ((SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_INPUT_FOCUS) == 0)
	{
		flushEvents();
	}

	m_inputState.update();
	return m_inputState;
}

void trd::Window::flushEvents()
{
	m_inputState.update();
}

void trd::Window::initSdl()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		throw ExternalLibraryException("trd::App::initSdl(): Failed to initialise SDL");
	}
}

void trd::Window::destroy()
{
	if (m_sdlTexture)
	{
		SDL_DestroyTexture(m_sdlTexture);
	}

	if (m_sdlRenderer)
	{
		SDL_DestroyRenderer(m_sdlRenderer);
	}

	if (m_sdlWindow)
	{
		SDL_DestroyWindow(m_sdlWindow);
	}
}
