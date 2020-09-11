#pragma once

#include "trTexture.hpp"
#include "trdRenderMode.hpp"
#include "trdLights.hpp"
#include "trQuadMask.hpp"
#include "trQuadVec2.hpp"
#include "trQuadVec3.hpp"

namespace trd
{
	class Shader
	{
	public:
		                   Shader();

		void               draw(const tr::QuadMask& mask, const tr::QuadVec3& screenPosition, const tr::QuadVec3& worldPosition, const tr::QuadVec3& normal, const tr::QuadVec2& textureCoord, tr::Color* color, float* depth) const;

		void               setTexture(const tr::Texture* const texture);
		void               setTextureFiltering(const bool textureFiltering);
		void               setRenderMode(const RenderMode& renderMode);
		void               setUseTexture(const bool useTexture);
		void               setBilinearFiltering(const bool bilinearFiltering);
		void               setAlpha(const float alpha);
		void               setLights(const Lights& lights);

		RenderMode         getRenderMode() const;

	private:
		const tr::Texture* m_texture;
		bool               m_textureFiltering;
		RenderMode         m_renderMode;
		bool               m_useTexture;
		bool               m_bilinearFiltering;
		float              m_alpha;
		Lights             m_lights;
	};
}