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
		                  Model(const tf::String& meshFilename, const MeshMap& meshMap, const Vector3& position, const Vector3& rotation, const bool fullBright);

		void              draw(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const;

		void              translate(const Vector3& translation);
		void              rotate(const Vector3& rotation);
		void              setPosition(const Vector3& position);
		void              setRotation(const Vector3& rotation);

	private:
		void              recalculateMatrix();

	private:
		const Mesh* const m_mesh;
		Matrix4           m_matrix;
		Vector3           m_position;
		Vector3           m_rotation;
		bool              m_fullBright;
	};
}