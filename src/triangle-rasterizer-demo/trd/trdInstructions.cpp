#include "trdInstructions.hpp"

void trd::Instructions::draw(const Settings& settings, tr::ColorBuffer& buffer)
{
	std::vector<tf::String> lines;

	lines.push_back(tf::String("WASD:  Move camera"));
	lines.push_back(tf::String("Space: Move camera up"));
	lines.push_back(tf::String("Ctrl:  Move camera down"));
	lines.push_back(tf::String(""));
	lines.push_back(tf::String("P:     Pause animation      {}",    { true ? "Paused" : "Not paused" }));
	lines.push_back(tf::String("R:     Resolution           {}x{}", { std::to_string(settings.getScreenSize().width), std::to_string(settings.getScreenSize().height) }));
	lines.push_back(tf::String("T:     Threads              {}",    { std::to_string(settings.getNumThreads()) }));
	lines.push_back(tf::String("H:     Horizontal FOV       {}",    { std::to_string(settings.getFov()) }));
	lines.push_back(tf::String("F:     Fragment shader mode {}",    { convertRenderModeToString(settings.getRenderMode()) }));
	lines.push_back(tf::String("M:     Texture mapping      {}",    { convertTextureModeToString(settings.getTextureMode()) }));
	lines.push_back(tf::String("B:     Bilinear filtering   {}",    { settings.getBilinearFiltering() ? "On" : "Off" }));
	lines.push_back(tf::String("I:     Instructions         {}",    { settings.getInstructionsEnabled() ? "Show" : "Hide" }));
	lines.push_back(tf::String("C:     Frame rate counter   {}",    { settings.getFrameRateEnabled() ? "Show" : "Hide" }));
	lines.push_back(tf::String("F11:   Fullscreen           {}",    { settings.getFullscreen() ? "Yes" : "No" }));

	drawText(lines, tr::Color(255, 255, 255, 255), Corner::BottomLeft, settings.getScreenSize(), buffer);
}

tf::String trd::Instructions::convertRenderModeToString(const RenderMode renderMode)
{
	switch (renderMode)
	{
	case RenderMode::Lit:         return "Lit";
	case RenderMode::FullBright:  return "Full bright";
	case RenderMode::Depth:       return "Depth";
	case RenderMode::Normals:     return "Normals";
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
