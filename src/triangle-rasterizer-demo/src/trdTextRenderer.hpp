#pragma once

#include "trColorBuffer.hpp"
#include "trdCorner.hpp"
#include "trdTextAlign.hpp"
#include "trdScreenPos.hpp"
#include "trdScreenSize.hpp"
#include "tfString.hpp"

namespace trd
{
	class TextRenderer
	{
	protected:
		static void             drawText(const std::vector<tf::String>& lines, const tr::Color& color, const ScreenPos& position, const TextAlign& alignment, tr::ColorBuffer& buffer);
		static void             drawText(const std::vector<tf::String>& lines, const tr::Color& color, const Corner corner, const ScreenSize& screenSize, tr::ColorBuffer& buffer);

	private:
		static size_t           calculateTextWidth(const std::vector<tf::String>& lines);

	private:
		static constexpr size_t s_fontWidth  = 8;
		static constexpr size_t s_fontHeight = 8;
		static constexpr size_t s_spacing    = 6;
	};
}