#include "trdInstructions.hpp"

void trd::Instructions::draw(const Settings& settings, tr::ColorBuffer& buffer)
{
	tf::Vector<tf::String> lines;

	lines.push_back(tf::String("1 Resolution:   {}x{}", { std::to_string(settings.getScreenSize().width), std::to_string(settings.getScreenSize().height) }));
	lines.push_back(tf::String("2 Fullscreen:   {}",    { settings.getFullscreen() ? "Yes" : "No" }));
	lines.push_back(tf::String("3 Render mode:  {}",    { convertRenderModeToString(settings.getRenderMode()) }));
	lines.push_back(tf::String("4 Threads:      {}",    { std::to_string(settings.getNumThreads()) }));
	lines.push_back(tf::String("5 Texture mode: {}",    { convertTextureModeToString(settings.getTextureMode()) }));

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::BottomLeft, settings.getScreenSize(), buffer);
}

tf::String trd::Instructions::convertRenderModeToString(const RenderMode renderMode)
{
	switch (renderMode)
	{
	case RenderMode::Lit:         return "Lit";
	case RenderMode::FullBright:  return "Full bright";
	case RenderMode::Textureless: return "Textureless";
	case RenderMode::Depth:       return "Depth";
	default:                      return "";
	}
}

tf::String trd::Instructions::convertTextureModeToString(const tr::TextureMode textureMode)
{
	switch (textureMode)
	{
	case tr::TextureMode::Affine:      return "Affine";
	case tr::TextureMode::Perspective: return "Perspective";
	default:                           return "";
	}
}
