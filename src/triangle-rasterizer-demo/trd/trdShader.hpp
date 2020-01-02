#pragma once

#include "trBlendMode.hpp"
#include "trTexture.hpp"
#include "trdRenderMode.hpp"
#include "trdLights.hpp"

namespace trd
{
	class Shader
	{
	public:
		                   Shader();

		void               draw(const Vector4& screenPosition, const Vector3& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color& color, float& depth) const;

		void               setTexture(const tr::Texture* const texture);
		void               setTextureFiltering(const bool textureFiltering);
		void               setRenderMode(const RenderMode& renderMode);
		void               setUseTexture(const bool useTexture);
		void               setBilinearFiltering(const bool bilinearFiltering);
		void               setBlendMode(const tr::BlendMode blendMode);
		void               setLights(const Lights& lights);

		RenderMode         getRenderMode() const;

	private:
		const tr::Texture* m_texture;
		bool               m_textureFiltering;
		RenderMode         m_renderMode;
		bool               m_useTexture;
		bool               m_bilinearFiltering;
		tr::BlendMode      m_blendMode;
		Lights             m_lights;
	};
}