#include "trdTextRenderer.hpp"
#include "font8x8_basic.h"

void trd::TextRenderer::drawText(const std::vector<tf::String>& lines, const tr::Color& color, const ScreenPos& position, const TextAlign& alignment, tr::ColorBuffer& buffer)
{
	const size_t textWidth = calculateTextWidth(lines);

	size_t y = position.y;

	for (const tf::String& line : lines)
	{
		size_t x = (alignment == TextAlign::Left) ? position.x : position.x + textWidth - line.size() * s_fontWidth;

		for (const char character : line)
		{
			for (const char row : font8x8_basic[character])
			{
				for (size_t column = 0; column < s_fontWidth; ++column)
				{
					if ((row >> column) & 1)
					{
						buffer.at(x + column, y) = color;
					}
				}

				++y;
			}

			x += s_fontWidth;
			y -= s_fontHeight;
		}

		y += s_fontHeight + s_spacing;
	}
}

void trd::TextRenderer::drawText(const std::vector<tf::String>& lines, const tr::Color& color, const Corner corner, const ScreenSize& screenSize, tr::ColorBuffer& buffer)
{
	const size_t textHeight = lines.size() * (s_fontHeight + s_spacing);
	const size_t textWidth  = calculateTextWidth(lines);

	switch (corner)
	{
	case Corner::TopLeft:     drawText(lines, color, { s_spacing,                                s_spacing },                      TextAlign::Left,  buffer); break;
	case Corner::TopRight:    drawText(lines, color, { screenSize.width - textWidth - s_spacing, s_spacing },                      TextAlign::Right, buffer); break;
	case Corner::BottomLeft:  drawText(lines, color, { s_spacing,                                screenSize.height - textHeight }, TextAlign::Left,  buffer); break;
	case Corner::BottomRight: drawText(lines, color, { screenSize.width - textWidth - s_spacing, screenSize.height - textHeight }, TextAlign::Right, buffer); break;
	}
}

size_t trd::TextRenderer::calculateTextWidth(const std::vector<tf::String>& lines)
{
	size_t textWidth  = 0;

	for (const tf::String& line : lines)
	{
		textWidth = std::max(textWidth, line.size() * s_fontWidth);
	}

	return textWidth;
}
