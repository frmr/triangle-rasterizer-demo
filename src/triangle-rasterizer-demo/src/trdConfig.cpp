#include "trdConfig.hpp"
#include "trdInvalidFileException.hpp"

trd::Config::Config() :
	tf::IniFile("trd.ini"),
	m_customScreenSize({ getU32("customResolutionX"), getU32("customResolutionY") }),
	m_customTileSize({ getU32("customTileX"), getU32("customTileY") }),
	m_mouseSensitivity(getFloat("mouseSensitivity"))
{
}

trd::ScreenSize trd::Config::getCustomScreenSize() const
{
	return m_customScreenSize;
}

trd::ScreenSize trd::Config::getCustomTileSize() const
{
	return m_customTileSize;
}

float trd::Config::getMouseSensitivity() const
{
	return m_mouseSensitivity;
}

uint32_t trd::Config::getU32(const tf::String& keyName) const
{
	try
	{
		const tf::String value = getString(keyName);
		return value.empty() ? 0u : uint32_t(std::stoul(getString(keyName)));
	}
	catch (const std::exception&)
	{
		throw InvalidFileException("trd::Config::getSizeT(): Invalid config key value (" + keyName + ")");
	}
}

float trd::Config::getFloat(const tf::String& keyName) const
{
	try
	{
		const tf::String value = getString(keyName);
		return value.empty() ? 0.0f : std::stof(value);
	}
	catch (const std::exception&)
	{
		throw InvalidFileException("trd::Config::getFloat(): Invalid config key value (" + keyName + ")");
	}
}

tf::String trd::Config::getString(const tf::String& keyName) const
{
	try
	{
		return getValue(keyName);
	}
	catch (const std::exception&)
	{
		return "";
	}
}
