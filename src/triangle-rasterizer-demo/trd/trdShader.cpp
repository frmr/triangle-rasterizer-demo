#include "trdShader.hpp"
#include <cassert>

trd::Shader::Shader() :
	m_texture(nullptr),
	m_textureFiltering(false),
	m_renderMode(trd::RenderMode::Lit),
	m_useTexture(true),
	m_bilinearFiltering(false),
	m_blendMode(tr::BlendMode::None)
{
}

void trd::Shader::draw(const Vector4& screenPosition, const Vector3& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color& color, float& depth) const
{
	depth = screenPosition.z;

	if (m_renderMode == RenderMode::Depth)
	{
		const uint8_t depthChannel = 255 - uint8_t((screenPosition.z + 1.0f) * 127.0f);
		color = tr::Color(depthChannel, depthChannel, depthChannel, 255);
	}
	else if (m_renderMode == RenderMode::Normals)
	{
		color = tr::Color(uint8_t(std::fabsf(normal.x) * 255.0f), uint8_t(std::fabsf(normal.y) * 255.0f), uint8_t(std::fabsf(normal.z) * 255.0f), 255);
	}
	else
	{
		const tr::Color textureColor       = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat) : tr::Color(255, 255, 255, 255);
		const Vector4   bufferColorFloat4  = color.toVector();
		const Vector4   textureColorFloat4 = textureColor.toVector();
		const float     normalizedAlpha    = textureColorFloat4.w / 255.0f;
		Vector3         preBlendColorFloat3;

		if (textureColor.a == 0)
		{
			return;
		}

		if (m_renderMode == RenderMode::Lit)
		{
			const Vector3   textureColorFloat(textureColorFloat4.z, textureColorFloat4.y, textureColorFloat4.x);

			for (const AmbientLight& light : m_lights.getAmbientLights())
			{
				preBlendColorFloat3 += textureColorFloat * light.getColor();
			}

			for (const DirectionalLight& light : m_lights.getDirectionalLights())
			{
				const float intensity = -light.getDirection().dot(normal);

				assert(intensity >= -1.0f && intensity <= 1.0f);

				if (intensity > 0.0f)
				{
					preBlendColorFloat3 += textureColorFloat * light.getColor() * intensity;
				}
			}

			for (const PointLight& light : m_lights.getPointLights())
			{
				Vector3 fragToLightVec = light.getPosition() - worldPosition;

				const float length = fragToLightVec.length();

				fragToLightVec *= 1.0f / length; // Looks strange but it's just an optimization

				const float intensity = fragToLightVec.dot(normal);

				//assert(intensity >= -1.0f && intensity <= 1.0f);

				if (intensity > 0.0f)
				{
					const float attenuation = length * light.getAttenuation();

					preBlendColorFloat3.x += textureColorFloat.x * std::max((light.getColor().x - attenuation), 0.0f) * intensity;
					preBlendColorFloat3.y += textureColorFloat.y * std::max((light.getColor().y - attenuation), 0.0f) * intensity;
					preBlendColorFloat3.z += textureColorFloat.z * std::max((light.getColor().z - attenuation), 0.0f) * intensity;
				}
			}

			preBlendColorFloat3.x = std::min(preBlendColorFloat3.x, 255.0f);
			preBlendColorFloat3.y = std::min(preBlendColorFloat3.y, 255.0f);
			preBlendColorFloat3.z = std::min(preBlendColorFloat3.z, 255.0f);
		}
		else
		{
			preBlendColorFloat3 = Vector3(textureColorFloat4.x, textureColorFloat4.y, textureColorFloat4.z);
		}

		if (m_blendMode == tr::BlendMode::WeightedAverage)
		{
			color = Vector3(
				preBlendColorFloat3.x * normalizedAlpha + bufferColorFloat4.x * (1.0f - normalizedAlpha),
				preBlendColorFloat3.y * normalizedAlpha + bufferColorFloat4.y * (1.0f - normalizedAlpha),
				preBlendColorFloat3.z * normalizedAlpha + bufferColorFloat4.z * (1.0f - normalizedAlpha)
			);
		}
		else
		{
			color = preBlendColorFloat3;
		}
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

void trd::Shader::setBilinearFiltering(const bool bilinearFiltering)
{
	m_bilinearFiltering = bilinearFiltering;
}

void trd::Shader::setBlendMode(const tr::BlendMode blendMode)
{
	m_blendMode = blendMode;
}

void trd::Shader::setLights(const Lights& lights)
{
	m_lights = lights;
}

trd::RenderMode trd::Shader::getRenderMode() const
{
	return m_renderMode;
}
