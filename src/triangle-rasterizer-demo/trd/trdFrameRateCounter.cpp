#include "trdFrameRateCounter.hpp"

trd::FrameRateCounter::FrameRateCounter() :
	m_timer(),
	m_frameCount(0),
	m_frameRate("0 FPS"),
	m_frameTime("0 MS ")
{
}

void trd::FrameRateCounter::draw(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const
{
	const std::vector<tf::String> lines = {
		m_frameRate,
		m_frameTime
	};

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::TopRight, screenSize, buffer);
}

void trd::FrameRateCounter::update()
{
	const double elapsed = m_timer.GetMilliseconds();

	++m_frameCount;

	if (elapsed >= 1000)
	{
		m_frameRate = std::to_string(int(double(m_frameCount) * (1000.0 / elapsed))) + " FPS";
		m_frameTime = toString(elapsed / double(m_frameCount), 2) + " MS "; 

		m_frameCount = 0;
		m_timer.Reset();
	}
}

tf::String trd::FrameRateCounter::toString(const double value, const uint8_t decimalPlaces)
{
	tf::String valueString = std::to_string(value);

	return valueString.substr(0, valueString.find(".") + decimalPlaces + 1);
}
