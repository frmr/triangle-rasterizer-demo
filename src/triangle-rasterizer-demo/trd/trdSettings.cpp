#include "trdSettings.hpp"
#include <thread>

trd::Settings::Settings() :
	m_screenSizeIndex(0),
	m_fullscreen(false),
	m_renderMode(RenderMode::Lit),
	m_numThreads(std::thread::hardware_concurrency()),
	m_textureMode(tr::TextureMode::Perspective)
{
	m_screenSizes.push_back({640,  480});
	m_screenSizes.push_back({1024, 768});
	m_screenSizes.push_back({1920, 1080}); // Read custom resolution from file

	//if (screenWidth <= 0 || screenHeight <= 0)
	//{
	//	return 0;
	//}

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
	case RenderMode::Lit:         m_renderMode = RenderMode::FullBright;  break;
	case RenderMode::FullBright:  m_renderMode = RenderMode::Textureless; break;
	case RenderMode::Textureless: m_renderMode = RenderMode::Depth;       break;
	case RenderMode::Depth:       m_renderMode = RenderMode::Lit;         break;
	}
}

void trd::Settings::cycleNumThreads()
{
	m_numThreads = m_numThreads % std::thread::hardware_concurrency() + 1;
}

void trd::Settings::cycleTextureMode()
{
	m_textureMode = (m_textureMode == tr::TextureMode::Affine) ? tr::TextureMode::Perspective : tr::TextureMode::Affine;
}

trd::ScreenSize trd::Settings::getScreenSize() const
{
	return m_screenSizes[m_screenSizeIndex];
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

tr::TextureMode trd::Settings::getTextureMode() const
{
	return m_textureMode;
}
