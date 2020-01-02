#include "trdHologramManager.hpp"
#include <filesystem>

trd::HologramManager::HologramManager(MeshMap& meshMap)
{
	loadModels(meshMap);
}

void trd::HologramManager::drawHologram(tr::Rasterizer<Shader>& rasterizer, Shader& shader, tr::ColorBuffer& colorBuffer, tr::DepthBuffer& depthBuffer) const
{
	if (m_holograms.empty())
	{
		return;
	}

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

	Model hologram = m_holograms[size_t(std::round(whole)) % m_holograms.size()];

	hologram.setRotation(Vector3(0.0f, rotation, 0.0f));

	if (fractional < delayRatio)
	{
		hologram.setScale(minScale);
		hologram.setPosition(Vector3(0.0f, minHeight, 0.0f));
	}
	else if (fractional < scaleUpRatio)
	{
		const float ratio  = (fractional - delayRatio) / (scaleUpRatio - delayRatio);
		const float scale  = minScale + (maxScale - minScale) * ratio;
		const float height = minHeight + (maxHeight - minHeight) * ratio;

		hologram.setScale(scale);
		hologram.setPosition(Vector3(0.0f, height, 0.0f));
	}
	else if (fractional < displayRatio)
	{
		hologram.setScale(maxScale);
		hologram.setPosition(Vector3(0.0f, maxHeight, 0.0f));
	}
	else if (fractional < scaleDownRatio)
	{
		const float ratio  = (fractional - displayRatio) / (scaleDownRatio - displayRatio);
		const float scale  = maxScale - (maxScale - minScale) * ratio;
		const float height = maxHeight - (maxHeight - minHeight) * ratio;

		hologram.setScale(scale);
		hologram.setPosition(Vector3(0.0f, height, 0.0f));
	}

	hologram.draw(rasterizer, shader, colorBuffer, depthBuffer);
}

void trd::HologramManager::update(const float frameTime)
{
	m_time += frameTime;
}

void trd::HologramManager::loadModels(MeshMap& meshMap)
{
	constexpr const char* hologramDirectory = "data/holograms";

	for (const auto& item : std::filesystem::directory_iterator(hologramDirectory))
	{
		if (std::filesystem::is_directory(item))
		{
			const std::filesystem::path subdirectory = item.path();
			std::filesystem::path       obj          = subdirectory;

			obj /= subdirectory.filename();
			obj += ".obj";

			if (std::filesystem::exists(obj))
			{
				m_holograms.emplace_back(obj.generic_string(), meshMap, Vector3(), Vector3(), true);
			}
		}
	}
}
