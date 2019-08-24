#pragma once

#include "tfString.hpp"
#include "trdMesh.hpp"

namespace trd
{
	class MeshMap
	{
	public:
		                                                           MeshMap(TextureMap& textureMap);

		const trd::Mesh*                                           get(const tf::String& filename);

	private:
		TextureMap&                                                m_textureMap;
		std::unordered_map<tf::String, std::unique_ptr<trd::Mesh>> m_meshes;
	};
}