#include "trdTextureMap.hpp"

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
	m_textures.emplace(filename, new tr::Texture(filename));
}