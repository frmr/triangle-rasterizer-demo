#pragma once

#include "trdScreenSize.hpp"
#include "trdRenderMode.hpp"
#include "trdTextureMode.hpp"
#include "trdInputState.hpp"
#include <vector>
#include <cstdint>

namespace trd
{
	class Settings
	{
	public:
		                        Settings(const ScreenSize& customScreenSize, const ScreenSize& customTileSize);

		void                    update(const InputState& inputState, bool& reinitWindow, bool& reinitCamera, bool& updateTiler);

		bool                    getPauseAnimation() const;
		ScreenSize              getScreenSize() const;
		ScreenSize              getTileSize() const;
		bool                    getFullscreen() const;
		RenderMode              getRenderMode() const;
		unsigned int            getNumThreads() const;
		uint8_t                 getFov() const;
		TextureMode             getTextureMode() const;
		bool                    getInstructionsEnabled() const;
		bool                    getFrameRateEnabled() const;
		bool                    getBilinearFiltering() const;
		bool                    getTakeScreenshot() const;

		void                    resetTakeScreenshot();

	private:
		void                    togglePauseAnimation();
		void                    cycleScreenSize();
		void                    cycleTileSize();
		void                    toggleFullscreen();
		void                    cycleRenderMode();
		void                    cycleNumThreads();
		void                    cycleFov();
		void                    cycleTextureMode();
		void                    toggleInstructionsEnabled();
		void                    toggleFrameRateEnabled();
		void                    toggleBilinearFiltering();

	private:
		bool                    m_pauseAnimation;
		std::vector<ScreenSize> m_screenSizes;
		size_t                  m_screenSizeIndex;
		std::vector<ScreenSize> m_tileSizes;
		size_t                  m_tileSizeIndex;
		bool                    m_fullscreen;
		RenderMode              m_renderMode;
		unsigned int            m_numThreads;
		std::vector<uint8_t>    m_fovs;
		size_t                  m_fovIndex;
		trd::TextureMode        m_textureMode;
		bool                    m_instructionsEnabled;
		bool                    m_frameRateEnabled;
		bool                    m_bilinearFiltering;
		bool                    m_takeScreenshot;
	};
}