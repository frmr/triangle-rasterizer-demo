#pragma once

#include <stdexcept>
#include "tfString.hpp"

namespace trd
{
	class InvalidFileException : public std::runtime_error
	{
	public:
		InvalidFileException(const tf::String& what) :
			std::runtime_error("InvalidFileException: " + what)
		{
		}
	};
}