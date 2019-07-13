#pragma once

#include "trRasterizer.hpp"
#include "trdCamera.hpp"
#include "trdMesh.hpp"
#include "trdMeshMap.hpp"
#include "trdTextureMap.hpp"
#include "Vectors.h"

namespace trd
{
	class Model
	{
	public:
		                  Model(const tf::String& meshFilename, const MeshMap& meshMap, const Vector3& position, const Vector2& rotation);

		void              draw(const Camera& camera, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

	private:
		const Mesh* const m_mesh;
		Matrix4           m_matrix;
	};
}