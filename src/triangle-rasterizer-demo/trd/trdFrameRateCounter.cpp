#include "trdFrameRateCounter.hpp"

trd::FrameRateCounter::FrameRateCounter() :
	m_timer(),
	m_frameCount(0),
	m_frameRate("0")
{
}

void trd::FrameRateCounter::draw(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const
{
	drawText({ m_frameRate }, tr::Color(255, 255, 255, 255), Corner::TopRight, screenSize, buffer);
}

void trd::FrameRateCounter::update()
{
	++m_frameCount;

	const double elapsed = m_timer.GetMilliseconds();

	if (elapsed >= 1000)
	{
		m_frameRate = std::to_string(int(double(m_frameCount) * (1000.0 / elapsed)));
		
		m_frameCount = 0;
		m_timer.Reset();
	}
}
