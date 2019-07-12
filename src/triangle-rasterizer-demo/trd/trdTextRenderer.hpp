#pragma once

#include "trColorBuffer.hpp"
#include "trdCorner.hpp"
#include "trdScreenPos.hpp"
#include "trdScreenSize.hpp"
#include "tfString.hpp"
#include "tfVector.hpp"

namespace trd
{
	class TextRenderer
	{
	protected:
		static void             drawText(const tf::Vector<tf::String>& lines, const tr::Color& color, const ScreenPos& position, tr::ColorBuffer& buffer);
		static void             drawText(const tf::Vector<tf::String>& lines, const tr::Color& color, const Corner corner, const ScreenSize& screenSize, tr::ColorBuffer& buffer);

	private:
		static constexpr size_t s_fontWidth  = 8;
		static constexpr size_t s_fontHeight = 8;
		static constexpr size_t s_spacing    = 2;
	};
}