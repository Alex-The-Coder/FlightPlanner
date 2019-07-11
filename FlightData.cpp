#include "FlightData.h"

FlightData::FlightData(String& destination, double cost, unsigned int time):
	destination(destination), cost(cost), time(time) {}

String& FlightData::getDestination()
{
	return destination;
}

double& FlightData::getCost()
{
	return cost;
}

unsigned int& FlightData::getTime()
{
	return time;
}
