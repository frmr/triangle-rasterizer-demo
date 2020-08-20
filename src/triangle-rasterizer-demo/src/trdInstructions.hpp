#pragma once

#include "trdTextRenderer.hpp"
#include "trdSettings.hpp"
#include "trTextureMode.hpp"

namespace trd
{
	class Instructions : public TextRenderer
	{
	public:
		static void       draw(const Settings& settings, tr::ColorBuffer& buffer);
	
	private:
		static tf::String convertRenderModeToString(const RenderMode renderMode);
		static tf::String convertTextureModeToString(const TextureMode textureMode);
	};
}