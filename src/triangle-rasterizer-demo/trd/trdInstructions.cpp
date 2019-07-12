#include "trdInstructions.hpp"

void trd::Instructions::draw(const Settings& settings, tr::ColorBuffer& buffer)
{
	tf::Vector<tf::String> lines;

	lines.push_back(tf::String("1 Resolution: {}x{}", { std::to_string(settings.getScreenSize().width), std::to_string(settings.getScreenSize().height) }));
	lines.push_back(tf::String("2 Fullscreen: {}",    { settings.getFullscreen() ? "Yes" : "No" }));

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::BottomLeft, settings.getScreenSize(), buffer);
}
