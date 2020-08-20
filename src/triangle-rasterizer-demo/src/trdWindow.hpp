#pragma once

#include "trdScreenSize.hpp"
#include "trdInputState.hpp"
#include "trColorBuffer.hpp"
#include "SDL.h"

namespace trd
{
	class Window
	{
	public:
		              Window();
		              ~Window();

		void          init(const ScreenSize& screenSize, const bool fullscreen);
		void          copyAndRender(tr::ColorBuffer& colorBuffer);
		InputState    getInputState();
		void          flushEvents();

	private:
		void          initSdl();
		void          destroy();

	private:
		SDL_Window*   m_sdlWindow;
		SDL_Renderer* m_sdlRenderer;
		SDL_Texture*  m_sdlTexture;
		InputState    m_inputState;
	};
}