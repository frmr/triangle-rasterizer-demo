#include "trdShader.hpp"
#include <cassert>

const tr::QuadFloat depthScale(12.0f);
const tr::QuadFloat allZeroes(0.0f);
const tr::QuadFloat allOnes(1.0f);
const tr::QuadFloat colorChannelMax(255.0f);
const tr::QuadColor white(colorChannelMax, colorChannelMax, colorChannelMax, colorChannelMax);
const Vector3       black(0.0f, 0.0f, 0.0f);

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
		tr::QuadColor(normal.x.abs() * colorChannelMax, normal.y.abs() * colorChannelMax, normal.z.abs() * colorChannelMax, colorChannelMax).write(color, mask);
	}
	else
	{
		const tr::QuadColor bufferColor(color, mask);
		const tr::QuadColor textureColor = m_useTexture ? m_texture->getAt(textureCoord.x, textureCoord.y, m_bilinearFiltering, tr::TextureWrappingMode::Repeat, mask) : white;
		const tr::QuadVec3  textureColorVec3 = textureColor.toVec3();
		const tr::QuadFloat normalizedAlpha = (textureColor.getAlpha() / 255.0f) * m_alpha;
		const tr::QuadFloat normalizedAlphaInverse = allOnes - normalizedAlpha;
		tr::QuadVec3        outputColor(black);
		
		if (m_renderMode == RenderMode::Lit)
		{
			for (const AmbientLight& light : m_lights.getAmbientLights())
			{
				outputColor += textureColorVec3 * light.getColor();
			}

			for (const DirectionalLight& light : m_lights.getDirectionalLights())
			{
				const tr::QuadFloat intensity             = -light.getDirection().dot(normal);
				const tr::QuadMask  positiveIntensityMask = intensity.greaterThan(allZeroes);
				const tr::QuadFloat maskedIntensity       = allZeroes.maskedCopy(intensity, positiveIntensityMask);

				outputColor += textureColorVec3 * light.getColor() * maskedIntensity;
			}

			for (const PointLight& light : m_lights.getPointLights())
			{
				tr::QuadVec3        fragToLightVec = light.getPosition() - worldPosition;
				const tr::QuadFloat length         = fragToLightVec.length();

				fragToLightVec /= length;

				const tr::QuadFloat intensity             = fragToLightVec.dot(normal);
				const tr::QuadMask  positiveIntensityMask = intensity.greaterThan(allZeroes);
				const tr::QuadFloat maskedIntensity       = allZeroes.maskedCopy(intensity, positiveIntensityMask);
				const tr::QuadFloat attenuation           = length * light.getAttenuation();

				outputColor.x += textureColorVec3.x * (light.getColor().x - attenuation).max(allZeroes) * maskedIntensity;
				outputColor.y += textureColorVec3.y * (light.getColor().y - attenuation).max(allZeroes) * maskedIntensity;
				outputColor.z += textureColorVec3.z * (light.getColor().z - attenuation).max(allZeroes) * maskedIntensity;
			}

			outputColor.x = outputColor.x.min(colorChannelMax);
			outputColor.y = outputColor.y.min(colorChannelMax);
			outputColor.z = outputColor.z.min(colorChannelMax);
		}
		else
		{
			outputColor = textureColorVec3;
		}

		outputColor = outputColor * normalizedAlpha + bufferColor.toVec3() * normalizedAlphaInverse;

		tr::QuadColor(outputColor.x, outputColor.y, outputColor.z, normalizedAlpha * 255.0f).write(color, mask);
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
