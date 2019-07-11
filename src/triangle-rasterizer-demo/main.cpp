#include <iostream>

#include "trd/trdApp.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Hello, world" << std::endl;

	trd::App app;

	return app.mainLoop();
}