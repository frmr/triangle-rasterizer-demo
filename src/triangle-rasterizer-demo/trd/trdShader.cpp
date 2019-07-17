#include "trdShader.hpp"

trd::Shader::Shader() :
	m_texture(nullptr),
	m_textureFiltering(false),
	m_renderMode(trd::RenderMode::Lit),
	m_useTexture(true)
{
}

void trd::Shader::draw(const Vector4& position, const Vector4& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color& color, float& depth) const
{
	depth = position.z;

	if (m_renderMode == RenderMode::Depth)
	{
		const uint8_t depthChannel = 255 - uint8_t((position.z + 1.0f) * 127.0f);
		color = tr::Color(depthChannel, depthChannel, depthChannel, 255);
	}
	else
	{
		color = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, false, tr::TextureWrappingMode::Repeat) : tr::Color(255, 255, 255, 255);
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

void trd::Shader::setUseTexture(const bool useTexture)
{
	m_useTexture = useTexture;
}
