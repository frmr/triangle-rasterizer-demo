#include "trdConfig.hpp"
#include "trdInvalidFileException.hpp"

trd::Config::Config() :
	tf::IniFile("trd.ini"),
	m_customScreenSize({ getSizeT("customResolutionX"), getSizeT("customResolutionY") }),
	m_mouseSensitivity(getFloat("mouseSensitivity"))
{
}

trd::ScreenSize trd::Config::getCustomScreenSize() const
{
	return m_customScreenSize;
}

float trd::Config::getMouseSensitivity() const
{
	return m_mouseSensitivity;
}

size_t trd::Config::getSizeT(const tf::String& keyName) const
{
	try
	{
		return std::stoull(getString(keyName));
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
		return std::stof(getString(keyName));
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
		return GetValue(keyName);
	}
	catch (const std::exception&)
	{
		return "";
	}
}
