#ifndef FLIGHTDATA_H_
#define FLIGHTDATA_H_

#include "String.h"

class FlightData
{
private:
	String destination;
	double cost;
	unsigned int time;
public:
	FlightData(String&, double, unsigned int);

	String& getDestination();
	double& getCost();
	unsigned int& getTime();
};

#endif /* FLIGHTDATA_H_ */
