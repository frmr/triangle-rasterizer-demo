#include "trdHologramManager.hpp"
#include "trdMissingFileException.hpp"
#include "tfIniFile.hpp"
#include <filesystem>

trd::HologramManager::HologramManager(MeshMap& meshMap) :
	m_height(0.0f),
	m_scale(0.0f)
{
	loadModels(meshMap);
}

void trd::HologramManager::drawHologram(const Vector3& cameraPosition, tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	shader.setBlendMode(tr::BlendMode::WeightedAverage);
	rasterizer.setCullFaceMode(tr::CullFaceMode::None);
	m_holograms[m_index].draw(cameraPosition, true, rasterizer, shader, colorBuffer, depthBuffer);
}

void trd::HologramManager::update(const float frameTime)
{
	m_time += frameTime;

	if (!m_holograms.empty())
	{
		updateHologram();
	}
}

trd::PointLight trd::HologramManager::getLight() const
{
	return PointLight(m_lightColors[m_index] * m_scale, Vector3(0.0f, m_height, 0.0f), 0.01f);
}

void trd::HologramManager::loadModels(MeshMap& meshMap)
{
	constexpr const char* hologramDirectory = "data/holograms";

	for (const auto& item : std::filesystem::directory_iterator(hologramDirectory))
	{
		if (std::filesystem::is_directory(item))
		{
			const std::filesystem::path subdirectory = item.path();
			const std::filesystem::path obj          = subdirectory / (subdirectory.filename().string() + ".obj");
			const std::filesystem::path ini          = subdirectory / (subdirectory.filename().string() + ".ini");

			if (!std::filesystem::exists(obj))
			{
				throw MissingFileException(obj.string());
			}

			if (!std::filesystem::exists(ini))
			{
				throw MissingFileException(ini.string());
			}

			m_holograms.emplace_back(obj.string(), meshMap, Vector3(), Vector3(), true);

			tf::IniFile IniFile(ini.string());

			m_lightColors.emplace_back(
				std::stof(IniFile.getValue("blue" )) / 255.0f,
				std::stof(IniFile.getValue("green")) / 255.0f,
				std::stof(IniFile.getValue("red"  )) / 255.0f
			);
		}
	}
}

void trd::HologramManager::updateHologram()
{
	constexpr float minHeight         = 0.0f;
	constexpr float maxHeight         = 5.0f;
	constexpr float minScale          = 0.0f;
	constexpr float maxScale          = 2.0f;
	constexpr float delayPeriod       = 1000.0f;
	constexpr float scalePeriod       = 1000.0f;
	constexpr float displayPeriod     = 5000.0f;
	constexpr float totalPeriod       = delayPeriod + scalePeriod * 2.0f + displayPeriod;
	constexpr float delayRatio        = delayPeriod / totalPeriod;
	constexpr float scaleUpRatio      = (delayPeriod + scalePeriod) / totalPeriod;
	constexpr float displayRatio      = (delayPeriod + scalePeriod + displayPeriod) / totalPeriod;
	constexpr float scaleDownRatio    = 1.0f;
	constexpr float rotationsPerCycle = 1.0f;
	constexpr float degreesPerCycle   = rotationsPerCycle * 360.0f;
	const float     progress          = m_time / totalPeriod;
	const float     rotation          = progress * degreesPerCycle;
	float           whole;
	float           fractional;

	fractional = std::modf(progress, &whole);
	m_index    = size_t(std::round(whole)) % m_holograms.size();

	if (fractional < delayRatio)
	{
		m_height = minHeight;
		m_scale  = minScale;
	}
	else if (fractional < scaleUpRatio)
	{
		const float ratio  = (fractional - delayRatio) / (scaleUpRatio - delayRatio);

		m_height = minHeight + (maxHeight - minHeight) * ratio;
		m_scale  = minScale + (maxScale - minScale) * ratio;
		
	}
	else if (fractional < displayRatio)
	{
		m_height = maxHeight;
		m_scale  = maxScale;
	}
	else if (fractional < scaleDownRatio)
	{
		const float ratio = (fractional - displayRatio) / (scaleDownRatio - displayRatio);

		m_height = maxHeight - (maxHeight - minHeight) * ratio;
		m_scale  = maxScale - (maxScale - minScale) * ratio;
	}

	m_holograms[m_index].setPosition(Vector3(0.0f, m_height, 0.0f));
	m_holograms[m_index].setRotation(Vector3(0.0f, rotation, 0.0f));
	m_holograms[m_index].setScale(m_scale);
}
