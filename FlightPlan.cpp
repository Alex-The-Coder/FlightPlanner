#include "FlightPlan.h"

FlightPlan::FlightPlan(String& origin, String& destination)
{
	hops.addElement(origin);
	hops.addElement(destination);
}

FlightPlan::FlightPlan(Stack<FlightData> data)
{
	while (!data.isEmpty())
	{
		FlightData d = data.pop();
		hops.insertElement(d.getDestination(), 0);
		cost += d.getCost();
		time += d.getTime();
	}
}

String FlightPlan::getOrigin()
{
	return hops.getElement(0);
}

String FlightPlan::getDestination()
{
	return hops.peekBack();
}

LinkedList<String> FlightPlan::getHops()
{
	return hops;
}

double FlightPlan::getCost()
{
	return cost;
}

unsigned int FlightPlan::getTime()
{
	return time;
}
