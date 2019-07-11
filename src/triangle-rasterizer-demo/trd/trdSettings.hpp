#pragma once

#include "tfVector.hpp"
#include "trdScreenSize.hpp"

namespace trd
{
	class Settings
	{
	public:
		                       Settings();

		void                   cycleScreenSize();
		void                   toggleFullscreen();

		ScreenSize             getScreenSize() const;
		bool                   getFullscreen() const;

	private:
		tf::Vector<ScreenSize> m_screenSizes;
		size_t                 m_screenSizeIndex;
		bool                   m_fullscreen;
	};
}