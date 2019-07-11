#pragma once

#include "tr.hpp"
#include "SDL.h"
#include "trdSettings.hpp"

namespace trd
{
	class App
	{
	public:
		              App();
		              ~App();

		int           mainLoop();

	private:
		void          initSdl();
		void          initWindow();
		void          deinitWindow();
		void          updateInputs();
		void          renderColorBufferToWindow();

	private:
		Settings      m_settings;
		bool          m_reinitWindow;
		bool          m_running;
		SDL_Window*   m_sdlWindow;
		SDL_Renderer* m_sdlRenderer;
		SDL_Texture*  m_sdlTexture;
	};
}