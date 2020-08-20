#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace trd
{
	class MissingFileException : public std::runtime_error
	{
	public:
		MissingFileException(const tf::String& what) :
			std::runtime_error("MissingFileException: " + what)
		{
		}
	};
}