#include "trdMeshMap.hpp"

trd::MeshMap::MeshMap(const TextureMap& textureMap)
{
	add("test.obj", textureMap);
}

const trd::Mesh* trd::MeshMap::get(const tf::String& filename) const
{
	return m_meshes.at(filename).get();
}

void trd::MeshMap::add(const tf::String& filename, const TextureMap& textureMap)
{
	m_meshes.emplace(filename, new trd::Mesh(filename, textureMap));
}