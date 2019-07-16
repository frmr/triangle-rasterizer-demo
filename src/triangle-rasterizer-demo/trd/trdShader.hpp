#pragma once

#include "trTexture.hpp"
#include "trdRenderMode.hpp"

namespace trd
{
	class Shader
	{
	public:
		                    Shader();

		void                draw(const Vector4& position, const Vector4& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color& color, float& depth) const;

		void                setTexture(const tr::Texture* const texture);
		void                setTextureFiltering(const bool textureFiltering);
		void                setRenderMode(const RenderMode& renderMode);

	private:
		const tr::Texture*  m_texture;
		bool                m_textureFiltering;
		RenderMode          m_renderMode;
	};
}