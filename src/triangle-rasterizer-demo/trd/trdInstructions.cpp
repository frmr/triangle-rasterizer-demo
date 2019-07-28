#include "trdInstructions.hpp"

void trd::Instructions::draw(const Settings& settings, tr::ColorBuffer& buffer)
{
	std::vector<tf::String> lines;

	lines.push_back(tf::String("1 Resolution:         {}x{}", { std::to_string(settings.getScreenSize().width), std::to_string(settings.getScreenSize().height) }));
	lines.push_back(tf::String("2 Fullscreen:         {}",    { settings.getFullscreen() ? "Yes" : "No" }));
	lines.push_back(tf::String("3 Threads:            {}",    { std::to_string(settings.getNumThreads()) }));
	lines.push_back(tf::String("5 Render mode:        {}",    { convertRenderModeToString(settings.getRenderMode()) }));
	lines.push_back(tf::String("6 Texture mode:       {}",    { convertTextureModeToString(settings.getTextureMode()) }));
	lines.push_back(tf::String("7 Bilinear filtering: {}",    { settings.getBilinearFiltering() ? "On" : "Off" }));
	lines.push_back(tf::String("8 Instructions:       {}",    { settings.getInstructionsEnabled() ? "Show" : "Hide" }));
	lines.push_back(tf::String("9 Frame rate:         {}",    { settings.getFrameRateEnabled() ? "Show" : "Hide" }));

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::BottomLeft, settings.getScreenSize(), buffer);
}

tf::String trd::Instructions::convertRenderModeToString(const RenderMode renderMode)
{
	switch (renderMode)
	{
	case RenderMode::Lit:         return "Lit";
	case RenderMode::FullBright:  return "Full bright";
	case RenderMode::Depth:       return "Depth";
	default:                      return "";
	}
}

tf::String trd::Instructions::convertTextureModeToString(const TextureMode textureMode)
{
	switch (textureMode)
	{
	case TextureMode::Off:         return "Off";
	case TextureMode::Affine:      return "Affine";
	case TextureMode::Perspective: return "Perspective";
	default:                       return "";
	}
}
