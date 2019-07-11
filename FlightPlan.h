#ifndef FLIGHTPLAN_H_
#define FLIGHTPLAN_H_

#include "FlightData.h"
#include "LinkedList.h"
#include "Stack.h"

class FlightPlan
{
private:
	LinkedList<String> hops;
	double cost = 0.0;
	unsigned int time = 0;
public:
	FlightPlan(String&, String&);
	FlightPlan(Stack<FlightData>);

	LinkedList<String> getHops();
	String getOrigin();
	String getDestination();
	double getCost();
	unsigned int getTime();
};

#endif /* FLIGHTPLAN_H_ */
