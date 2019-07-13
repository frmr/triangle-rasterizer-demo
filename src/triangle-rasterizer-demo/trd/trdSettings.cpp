#include "trdSettings.hpp"

trd::Settings::Settings() :
	m_screenSizeIndex(0),
	m_fullscreen(false),
	m_renderMode(RenderMode::Lit)
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
