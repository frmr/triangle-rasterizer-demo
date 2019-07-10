#include <iostream>

#include "trd/trdApp.hpp"

int main()
{
	std::cout << "Hello, world" << std::endl;

	trd::App app;

	return app.MainLoop();
}