#include "trdFrameTimer.hpp"

trd::FrameTimer::FrameTimer() :
	m_frameTimer(),
	m_frameTime(0.0f),
	m_cumulativeFrameTime(0.0f),
	m_frameCount(0),
	m_averageFrameTime(0.0f)
{
}

void trd::FrameTimer::draw(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const
{
	if (m_averageFrameTime > 0.0f)
	{
		const std::vector<tf::String> lines = {
			toString(1000.0f / m_averageFrameTime, 2) + " FPS",
			toString(m_averageFrameTime, 2) + " MS "
		};

		drawText(lines, tr::Color(255, 255, 255, 255), Corner::TopRight, screenSize, buffer);
	}
}

void trd::FrameTimer::update()
{
	m_frameTime = float(m_frameTimer.getMilliseconds());

	m_frameTimer.reset();

	m_cumulativeFrameTime += m_frameTime;
	++m_frameCount;

	if (m_cumulativeFrameTime >= s_samplePeriod)
	{
		m_averageFrameTime    = m_cumulativeFrameTime / m_frameCount;
		m_cumulativeFrameTime = 0.0f;
		m_frameCount          = 0;
	}
}

float trd::FrameTimer::getFrameTime() const
{
	return m_frameTime;
}

float trd::FrameTimer::getDeltaTime() const
{
	return m_frameTime;
}

tf::String trd::FrameTimer::toString(const double value, const uint8_t decimalPlaces)
{
	const tf::String valueString = std::to_string(value);

	return valueString.substr(0, valueString.find(".") + decimalPlaces + 1);
}
