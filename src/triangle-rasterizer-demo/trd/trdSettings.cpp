#include "trdSettings.hpp"

trd::Settings::Settings() :
	m_screenSizeIndex(0),
	m_fullscreen(false)
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

trd::ScreenSize trd::Settings::getScreenSize() const
{
	return m_screenSizes[m_screenSizeIndex];
}

bool trd::Settings::getFullscreen() const
{
	return m_fullscreen;
}
