#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "FlightPlanner.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 4)
	{
		Catch::Session().run();
		return 0;
	}

	FlightPlanner fp(argv[1], argv[2], argv[3]);
	return 0;
}
