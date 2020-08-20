#include "trdTextRenderer.hpp"
#include "trdFont.hpp"

void trd::TextRenderer::drawText(const std::vector<tf::String>& lines, const tr::Color& color, const ScreenPos& position, const TextAlign& alignment, tr::ColorBuffer& buffer)
{
	const size_t textWidth = calculateTextWidth(lines);

	size_t y = position.y;

	for (const tf::String& line : lines)
	{
		size_t x = (alignment == TextAlign::Left) ? position.x : position.x + textWidth - line.size() * s_fontWidth;

		for (const unsigned char character : line)
		{
			for (const unsigned char row : trd::font[character])
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
	const size_t    textHeight  = lines.size() * (s_fontHeight + s_spacing) - s_spacing;
	const size_t    textWidth   = calculateTextWidth(lines);
	const ScreenPos screenBounds = { screenSize.width - 1, screenSize.height - 1 };

	size_t top, left, bottom, right;

	switch (corner)
	{
	case Corner::TopLeft:
		top    = 0;
		left   = 0;
		bottom = textHeight + s_spacing * 2;
		right  = textWidth  + s_spacing * 2;
		break;
	case Corner::TopRight:
		top    = 0;
		left   = screenBounds.x - textWidth - s_spacing * 2;
		bottom = textHeight + s_spacing * 2;
		right  = screenBounds.x;
		break;
	case Corner::BottomLeft:
		top    = screenBounds.y - textHeight - s_spacing * 2;
		left   = 0;
		bottom = screenBounds.y;
		right  = textWidth + s_spacing * 2;
		break;
	case Corner::BottomRight:
		top    = screenBounds.y - textHeight - s_spacing * 2;
		left   = screenBounds.x - textWidth - s_spacing * 2;
		bottom = screenBounds.y;
		right  = screenBounds.x;
		break;
	}

	for (size_t y = top; y <= bottom; ++y)
	{
		for (size_t x = left; x <= right; ++x)
		{
			tr::Color& pixel = buffer.at(x, y);

			pixel.r /= 2;
			pixel.g /= 2;
			pixel.b /= 2;
		}
	}

	switch (corner)
	{
	case Corner::TopLeft:
	case Corner::BottomLeft:
		drawText(lines, color, { left + s_spacing, top + s_spacing }, TextAlign::Left, buffer);
		break;
	case Corner::TopRight:
	case Corner::BottomRight:
		drawText(lines, color, { left + s_spacing, top + s_spacing }, TextAlign::Right, buffer);
		break;
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
