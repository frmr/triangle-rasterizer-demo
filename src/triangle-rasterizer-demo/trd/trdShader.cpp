#include "trdShader.hpp"

trd::Shader::Shader() :
	m_texture(nullptr),
	m_textureFiltering(false),
	m_renderMode(trd::RenderMode::Lit)
{
}

void trd::Shader::draw(const Vector4& position, const Vector4& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color* const color, float* const depth) const
{
	switch (m_renderMode)
	{
	case trd::RenderMode::Lit:
		*color = m_texture->getAt(textureCoord.x, textureCoord.y, false, tr::TextureWrappingMode::Repeat);
		break;
	case trd::RenderMode::FullBright:
		*color = tr::Color(255, 0, 0, 255);
		break;
	case trd::RenderMode::Textureless:
		*color = tr::Color(0, 255, 0, 255);
		break;
	case trd::RenderMode::Depth:
		*color = tr::Color(0, 0, 255, 255);
		break;
	}
}

void trd::Shader::setTexture(const tr::Texture* const texture)
{
	m_texture = texture;
}

void trd::Shader::setTextureFiltering(const bool textureFiltering)
{
	m_textureFiltering = textureFiltering;
}

void trd::Shader::setRenderMode(const RenderMode& renderMode)
{
	m_renderMode = renderMode;
}
