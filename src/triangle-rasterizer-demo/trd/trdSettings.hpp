#pragma once

#include "trdScreenSize.hpp"
#include "trdRenderMode.hpp"
#include "trdTextureMode.hpp"
#include <vector>

namespace trd
{
	class Settings
	{
	public:
		                        Settings();

		void                    cycleScreenSize();
		void                    toggleFullscreen();
		void                    cycleRenderMode();
		void                    cycleNumThreads();
		void                    cycleTextureMode();
		void                    toggleInstructionsEnabled();
		void                    toggleFrameRateEnabled();
		void                    toggleBilinearFiltering();

		ScreenSize              getScreenSize() const;
		bool                    getFullscreen() const;
		RenderMode              getRenderMode() const;
		unsigned int            getNumThreads() const;
		TextureMode             getTextureMode() const;
		bool                    getInstructionsEnabled() const;
		bool                    getFrameRateEnabled() const;
		bool                    getBilinearFiltering() const;

	private:
		std::vector<ScreenSize> m_screenSizes;
		size_t                  m_screenSizeIndex;
		bool                    m_fullscreen;
		RenderMode              m_renderMode;
		unsigned int            m_numThreads;
		trd::TextureMode        m_textureMode;
		bool                    m_instructionsEnabled;
		bool                    m_frameRateEnabled;
		bool                    m_bilinearFiltering;
	};
}