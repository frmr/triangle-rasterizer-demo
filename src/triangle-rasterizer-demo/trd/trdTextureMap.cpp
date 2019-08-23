#include "trdTextureMap.hpp"
#include "lodepng.h"

trd::TextureMap::TextureMap()
{
	add("data/textures/test.png");
	add("data/textures/earth.png");
	add("data/textures/sofa.png");
	add("data/textures/window.png");
	add("data/textures/coffee-table.png");
}

const tr::Texture* trd::TextureMap::get(const tf::String& filename) const
{
	return m_textures.at(filename).get();
}

void trd::TextureMap::add(const tf::String& filename)
{
	std::vector<uint8_t> encodedData;

	if (!lodepng::load_file(encodedData, filename))
	{
		uint32_t             width;
		uint32_t             height;
		lodepng::State       state;
		std::vector<uint8_t> decodedData;

		state.info_raw.colortype = LodePNGColorType::LCT_RGBA;

		if (!lodepng::decode(decodedData, width, height, state, encodedData))
		{
			m_textures.emplace(filename, new tr::Texture(width, height, decodedData));
		}
	}
}