#pragma once

#include "trdTextRenderer.hpp"
#include "tfTimer.hpp"

namespace trd
{
	class FrameRateCounter : public TextRenderer
	{
	public:
		                  FrameRateCounter();

		void              draw(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const;
		void              update();

	private:
		static tf::String toString(const double value, const uint8_t decimalPlaces);

	private:
		tf::Timer         m_timer;
		size_t            m_frameCount;
		tf::String        m_frameRate;
		tf::String        m_frameTime;
	};
}