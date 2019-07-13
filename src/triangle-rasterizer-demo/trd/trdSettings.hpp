#pragma once

#include "tfVector.hpp"
#include "trdScreenSize.hpp"
#include "trdRenderMode.hpp"

namespace trd
{
	class Settings
	{
	public:
		                       Settings();

		void                   cycleScreenSize();
		void                   toggleFullscreen();
		void                   cycleRenderMode();

		ScreenSize             getScreenSize() const;
		bool                   getFullscreen() const;
		RenderMode             getRenderMode() const;

	private:
		tf::Vector<ScreenSize> m_screenSizes;
		size_t                 m_screenSizeIndex;
		bool                   m_fullscreen;
		RenderMode             m_renderMode;
	};
}