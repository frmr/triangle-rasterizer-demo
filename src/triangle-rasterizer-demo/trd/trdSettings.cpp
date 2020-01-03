#include "trdSettings.hpp"
#include <thread>

trd::Settings::Settings(const ScreenSize& customScreenSize) :
	m_pauseAnimation(false),
	m_screenSizeIndex(0),
	m_fullscreen(false),
	m_renderMode(RenderMode::Lit),
	m_numThreads(std::thread::hardware_concurrency()),
	m_fovIndex(2),
	m_textureMode(TextureMode::Perspective),
	m_instructionsEnabled(true),
	m_frameRateEnabled(true),
	m_bilinearFiltering(false)
{
	m_screenSizes.push_back({  640,  480 });
	m_screenSizes.push_back({ 1024,  768 });

	if (customScreenSize.width > 0 && customScreenSize.height > 0)
	{
		m_screenSizes.push_back(customScreenSize);
	}

	m_fovs.push_back(60);
	m_fovs.push_back(90);
	m_fovs.push_back(110);
}

void trd::Settings::update(const InputState& inputState, bool& reinitWindow, bool& reinitCamera)
{
	reinitWindow = false;
	reinitCamera = false;

	if (inputState.getKeyState(Key::ChangeSettingPauseAnimation    ).pressed) { togglePauseAnimation();                           }
	if (inputState.getKeyState(Key::ChangeSettingResolution        ).pressed) { cycleScreenSize();           reinitWindow = true; }
	if (inputState.getKeyState(Key::ChangeSettingThreads           ).pressed) { cycleNumThreads();                                }
	if (inputState.getKeyState(Key::ChangeSettingHorizontalFov     ).pressed) { cycleFov();                  reinitCamera = true; }
	if (inputState.getKeyState(Key::ChangeSettingFragmentShaderMode).pressed) { cycleRenderMode();                                }
	if (inputState.getKeyState(Key::ChangeSettingTextureMapping    ).pressed) { cycleTextureMode();                               }
	if (inputState.getKeyState(Key::ChangeSettingBilinearFiltering ).pressed) { toggleBilinearFiltering();                        }
	if (inputState.getKeyState(Key::ChangeSettingInstructions      ).pressed) { toggleInstructionsEnabled();                      }
	if (inputState.getKeyState(Key::ChangeSettingFrameRateCounter  ).pressed) { toggleFrameRateEnabled();                         }
	if (inputState.getKeyState(Key::ChangeSettingFullscreen        ).pressed) { toggleFullscreen();          reinitWindow = true; }
}

void trd::Settings::togglePauseAnimation()
{
	m_pauseAnimation = !m_pauseAnimation;
}

void trd::Settings::cycleScreenSize()
{
	++m_screenSizeIndex %= m_screenSizes.size();
}

void trd::Settings::toggleFullscreen()
{
	m_fullscreen = !m_fullscreen;
}

void trd::Settings::cycleRenderMode()
{
	switch (m_renderMode)
	{
	case RenderMode::Lit:         m_renderMode = RenderMode::FullBright; break;
	case RenderMode::FullBright:  m_renderMode = RenderMode::Depth;      break;
	case RenderMode::Depth:       m_renderMode = RenderMode::Normals;    break;
	case RenderMode::Normals:     m_renderMode = RenderMode::Lit;        break;
	}
}

void trd::Settings::cycleNumThreads()
{
	m_numThreads = m_numThreads % std::thread::hardware_concurrency() + 1;
}

void trd::Settings::cycleFov()
{
	++m_fovIndex %= m_fovs.size();
}

void trd::Settings::cycleTextureMode()
{
	switch (m_textureMode)
	{
	case TextureMode::Off:         m_textureMode = TextureMode::Affine;      break;
	case TextureMode::Affine:      m_textureMode = TextureMode::Perspective; break;
	case TextureMode::Perspective: m_textureMode = TextureMode::Off;         break;
	}
}

void trd::Settings::toggleInstructionsEnabled()
{
	m_instructionsEnabled = !m_instructionsEnabled;
}

void trd::Settings::toggleFrameRateEnabled()
{
	m_frameRateEnabled = !m_frameRateEnabled;
}

void trd::Settings::toggleBilinearFiltering()
{
	m_bilinearFiltering = !m_bilinearFiltering;
}

bool trd::Settings::getPauseAnimation() const
{
	return m_pauseAnimation;
}

trd::ScreenSize trd::Settings::getScreenSize() const
{
	return m_screenSizes.at(m_screenSizeIndex);
}

bool trd::Settings::getFullscreen() const
{
	return m_fullscreen;
}

trd::RenderMode trd::Settings::getRenderMode() const
{
	return m_renderMode;
}

unsigned int trd::Settings::getNumThreads() const
{
	return m_numThreads;
}

uint8_t trd::Settings::getFov() const
{
	return m_fovs.at(m_fovIndex);
}

trd::TextureMode trd::Settings::getTextureMode() const
{
	return m_textureMode;
}

bool trd::Settings::getInstructionsEnabled() const
{
	return m_instructionsEnabled;
}

bool trd::Settings::getFrameRateEnabled() const
{
	return m_frameRateEnabled;
}

bool trd::Settings::getBilinearFiltering() const
{
	return m_bilinearFiltering;
}
