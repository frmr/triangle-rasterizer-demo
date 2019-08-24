#include "trdShader.hpp"
#include <cassert>

trd::Shader::Shader() :
	m_texture(nullptr),
	m_textureFiltering(false),
	m_renderMode(trd::RenderMode::Lit),
	m_useTexture(true),
	m_bilinearFiltering(false)
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
		color = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat) : tr::Color(255, 255, 255, 255);

		if (m_renderMode == RenderMode::Lit)
		{
			const Vector4 colorFloat4 = color.toVector();
			const Vector3 colorFloat(colorFloat4.x, colorFloat4.y, colorFloat4.z);
			Vector3       postLightColor(0.0f, 0.0f, 0.0f);

			for (const AmbientLight& light : m_lights.getAmbientLights())
			{
				postLightColor += colorFloat * light.getColor();
			}

			for (const DirectionalLight& light : m_lights.getDirectionalLights())
			{
				const float intensity = -light.getDirection().dot(normal);

				assert(intensity >= -1.0f && intensity <= 1.0f);

				if (intensity > 0.0f)
				{
					postLightColor += colorFloat * light.getColor() * intensity;
				}
			}

			for (const PointLight& light : m_lights.getPointLights())
			{
				Vector3 fragToLightVec = light.getPosition() - worldPosition;

				const float length = fragToLightVec.length();

				fragToLightVec *= 1.0f / length; // Looks strange but it's just an optimization

				const float intensity = fragToLightVec.dot(normal);

				assert(intensity >= -1.0f && intensity <= 1.0f);

				if (intensity > 0.0f)
				{
					const float attenuation = length * light.getAttenuation();

					postLightColor.x += colorFloat.x * std::max((light.getColor().x - attenuation), 0.0f) * intensity;
					postLightColor.y += colorFloat.y * std::max((light.getColor().y - attenuation), 0.0f) * intensity;
					postLightColor.z += colorFloat.z * std::max((light.getColor().z - attenuation), 0.0f) * intensity;
				}
			}

			postLightColor.x = std::min(postLightColor.x, 255.0f);
			postLightColor.y = std::min(postLightColor.y, 255.0f);
			postLightColor.z = std::min(postLightColor.z, 255.0f);

			color = postLightColor;
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

void trd::Shader::setLights(const Lights& lights)
{
	m_lights = lights;
}

trd::RenderMode trd::Shader::getRenderMode() const
{
	return m_renderMode;
}
