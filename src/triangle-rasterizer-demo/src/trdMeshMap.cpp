#include "trdMeshMap.hpp"

trd::MeshMap::MeshMap(TextureMap& textureMap) :
	m_textureMap(textureMap)
{
}

const trd::Mesh* trd::MeshMap::get(const tf::String& filename)
{
	const auto iterator = m_meshes.find(filename);

	if (iterator == m_meshes.end())
	{
		return m_meshes.emplace(filename, new trd::Mesh(filename, m_textureMap)).first->second.get();
	}
	else
	{
		return iterator->second.get();
	}
}