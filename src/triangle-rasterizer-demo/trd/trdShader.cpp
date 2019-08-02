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

void trd::Shader::draw(const Vector4& screenPosition, const Vector4& worldPosition, const Vector3& normal, const Vector2& textureCoord, tr::Color& color, float& depth) const
{
	depth = screenPosition.z;

	if (m_renderMode == RenderMode::Depth)
	{
		const uint8_t depthChannel = 255 - uint8_t((screenPosition.z + 1.0f) * 127.0f);
		color = tr::Color(depthChannel, depthChannel, depthChannel, 255);
	}
	else
	{
		color = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat) : tr::Color(255, 255, 255, 255);

		if (m_renderMode == RenderMode::Lit)
		{
			const Vector4 colorFloat = color.toVector() / 255.0f;
			Vector4       postLightColor(0.0f, 0.0f, 0.0f, colorFloat.w);

			for (const AmbientLight& light : m_lights.getAmbientLights())
			{
				postLightColor.x += colorFloat.x * light.getColor().x;
				postLightColor.y += colorFloat.y * light.getColor().y;
				postLightColor.z += colorFloat.z * light.getColor().z;
			}

			for (const DirectionalLight& light : m_lights.getDirectionalLights())
			{
				const float intensity = -light.getDirection().dot(normal);

				assert(intensity >= -1.0f && intensity <= 1.0f);

				if (intensity > 0.0f)
				{
					postLightColor.x += colorFloat.x * light.getColor().x * intensity;
					postLightColor.y += colorFloat.y * light.getColor().y * intensity;
					postLightColor.z += colorFloat.z * light.getColor().z * intensity;
				}
			}

			for (const PointLight& light : m_lights.getPointLights())
			{
				Vector3 fragToLightVec(
					light.getPosition().x - worldPosition.x,
					light.getPosition().y - worldPosition.y,
					light.getPosition().z - worldPosition.z
				);

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

			postLightColor.x = std::min(postLightColor.x, 1.0f);
			postLightColor.y = std::min(postLightColor.y, 1.0f);
			postLightColor.z = std::min(postLightColor.z, 1.0f);
			
			color = postLightColor * 255.0f;
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
