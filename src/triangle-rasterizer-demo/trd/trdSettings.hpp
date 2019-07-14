#pragma once

#include "tfVector.hpp"
#include "trdScreenSize.hpp"
#include "trdRenderMode.hpp"
#include "trTextureMode.hpp"

namespace trd
{
	class Settings
	{
	public:
		                       Settings();

		void                   cycleScreenSize();
		void                   toggleFullscreen();
		void                   cycleRenderMode();
		void                   cycleNumThreads();
		void                   cycleTextureMode();

		ScreenSize             getScreenSize() const;
		bool                   getFullscreen() const;
		RenderMode             getRenderMode() const;
		unsigned int           getNumThreads() const;
		tr::TextureMode        getTextureMode() const;

	private:
		tf::Vector<ScreenSize> m_screenSizes;
		size_t                 m_screenSizeIndex;
		bool                   m_fullscreen;
		RenderMode             m_renderMode;
		unsigned int           m_numThreads;
		tr::TextureMode        m_textureMode;
	};
}