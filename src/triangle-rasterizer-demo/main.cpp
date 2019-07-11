#include <iostream>

#include "trd/trdApp.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Hello, world" << std::endl;

	try
	{
		trd::App app;
		app.mainLoop();

		return 0;
	}
	catch (const std::exception e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "Unknown exception" << std::endl;
	}

	return 1;
}