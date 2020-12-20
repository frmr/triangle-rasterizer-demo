#include "trdShader.hpp"
#include <cassert>

const tr::QuadFloat depthScale(12.0f);
const tr::QuadFloat allOnes(1.0f);
const tr::QuadFloat colorChannelMax(255.0f);
const tr::QuadColor white(colorChannelMax, colorChannelMax, colorChannelMax, colorChannelMax);

trd::Shader::Shader() :
	m_texture(nullptr),
	m_textureFiltering(false),
	m_renderMode(trd::RenderMode::Lit),
	m_useTexture(true),
	m_bilinearFiltering(false),
	m_alpha(1.0f)
{
}

void trd::Shader::draw(const tr::QuadMask& mask, const tr::QuadVec3& screenPosition, const tr::QuadVec3& worldPosition, const tr::QuadVec3& normal, const tr::QuadVec2& textureCoord, tr::Color* color, float* depth) const
{
	screenPosition.z.write(depth, mask);

	if (m_renderMode == RenderMode::Depth)
	{
		const tr::QuadFloat adjustedDepth = screenPosition.z + allOnes;
		const tr::QuadFloat depthChannel  = colorChannelMax - (((adjustedDepth * adjustedDepth * adjustedDepth) / depthScale) * colorChannelMax);

		tr::QuadColor(depthChannel, depthChannel, depthChannel, colorChannelMax).write(color, mask);
	}
	else if (m_renderMode == RenderMode::Normals)
	{
		//color = tr::Color(uint8_t(std::abs(normal.x) * 255.0f), uint8_t(std::abs(normal.y) * 255.0f), uint8_t(std::abs(normal.z) * 255.0f), 255);

		tr::QuadColor(normal.x.abs() * colorChannelMax, normal.y.abs() * colorChannelMax, normal.z.abs() * colorChannelMax, colorChannelMax).write(color, mask);
	}
	else
	{
		//const tr::QuadColor textureColor = m_texture->getAt(textureCoord.x, textureCoord.y, mask);
		const tr::QuadColor textureColor = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat, mask) : white;

		textureColor.write(color, mask);
	}
	/*
		const tr::Color textureColor       = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat) : tr::Color(255, 255, 255, 255);
		const Vector4   bufferColorFloat4  = color.toVector();
		const Vector4   textureColorFloat4 = textureColor.toVector();
		const float     alpha              = m_alpha * (textureColorFloat4.w / 255.0f);
		Vector3         preBlendColorFloat3;

		if (alpha == 0.0f)
		{
			return;
		}

		if (m_renderMode == RenderMode::Lit)
		{
			const Vector3 textureColorFloat(textureColorFloat4.z, textureColorFloat4.y, textureColorFloat4.x);

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

		if (alpha < 1.0f)
		{
			color = Vector3(
				preBlendColorFloat3.x * alpha + bufferColorFloat4.x * (1.0f - alpha),
				preBlendColorFloat3.y * alpha + bufferColorFloat4.y * (1.0f - alpha),
				preBlendColorFloat3.z * alpha + bufferColorFloat4.z * (1.0f - alpha)
			);
		}
		else
		{
			color = preBlendColorFloat3;
		}


		*/



	//}
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

void trd::Shader::setAlpha(const float alpha)
{
	m_alpha = alpha;
}

void trd::Shader::setLights(const Lights& lights)
{
	m_lights = lights;
}

trd::RenderMode trd::Shader::getRenderMode() const
{
	return m_renderMode;
}
