#include "trdTextureMap.hpp"

trd::TextureMap::TextureMap()
{
	add("data/textures/test.png");
}

const tr::Texture* trd::TextureMap::get(const tf::String& filename) const
{
	return m_textures.at(filename).get();
}

void trd::TextureMap::add(const tf::String& filename)
{
	m_textures.emplace(filename, new tr::Texture(filename));
}