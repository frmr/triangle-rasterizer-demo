#pragma once

#include "tfString.hpp"
#include "tfUnorderedMap.hpp"
#include "trdMesh.hpp"

namespace trd
{
	class MeshMap
	{
	public:
		                                                         MeshMap(const TextureMap& textureMap);

		const trd::Mesh*                                         get(const tf::String& filename) const;

	private:
		void                                                     add(const tf::String& filename, const TextureMap& textureMap);

	private:
		tf::UnorderedMap<tf::String, std::unique_ptr<trd::Mesh>> m_meshes;
	};
}