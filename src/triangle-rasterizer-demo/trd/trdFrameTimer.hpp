#pragma once

#include "trdTextRenderer.hpp"
#include "tfTimer.hpp"

namespace trd
{
	class FrameTimer : public TextRenderer
	{
	public:
		                  FrameTimer();

		void              draw(const ScreenSize& screenSize, tr::ColorBuffer& buffer) const;
		void              update();
		float             getFrameTime() const;
		float             getDeltaTime() const;

	private:
		static tf::String toString(const double value, const uint8_t decimalPlaces);

	private:
		tf::Timer         m_frameTimer;
		float             m_frameTime;
		float             m_cumulativeFrameTime;
		size_t            m_frameCount;
		float             m_averageFrameTime;
	};
}