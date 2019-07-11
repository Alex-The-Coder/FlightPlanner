#ifndef FLIGHTPLANNER_H_
#define FLIGHTPLANNER_H_

#include "AdjacencyList.h"
#include "FlightData.h"
#include "FlightPlan.h"
#include "LinkedList.h"
#include "SortedList.h"
#include "String.h"

class FlightPlanner
{
private:
	AdjacencyList<String, LinkedList<FlightData>> graph = AdjacencyList<String, LinkedList<FlightData>>(LinkedList<FlightData>(), [](const String& key)
	{
		return key.getHashCode();
	});
public:
	FlightPlanner(char*, char*, char*);
private:
	void addRoute(String&, String&, double, unsigned int);
	SortedList<FlightPlan> getRoutes(String&, String&, bool);
};

#endif /* FLIGHTPLANNER_H_ */
