#include "trdTextureMap.hpp"

void trd::TextureMap::add(const tf::String& filename)
{
	m_textures.emplace(filename, new tr::Texture(filename));
}

const tr::Texture* trd::TextureMap::get(const tf::String& filename) const
{
	return m_textures.at(filename).get();
}
