#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace trd
{
	class UnsupportedFileException : public std::runtime_error
	{
	public:
		UnsupportedFileException(const tf::String& what) :
			std::runtime_error("UnsupportedFileException: " + what)
		{
		}
	};
}