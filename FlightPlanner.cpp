#include "FlightPlanner.h"
#include <fstream>
#include "Stack.h"

using namespace std;

void repairInputStream(ifstream& input)
{
	char c;
	input.get(c);
    
	if (c == '\r')
	{
		input.get(c);
	}
}

FlightPlanner::FlightPlanner(char* graphInputName, char* requestInputName, char* outputName)
{
	ifstream graphInput(graphInputName);

	if (!graphInput.good())
	{
		return;
	}

	int graphTotal;
	graphInput >> graphTotal;

	for (int i = 0; i < graphTotal; i++)
	{
		repairInputStream(graphInput);
		String origin;
		String destination;
		unsigned int time;
		double cost;

		getline(graphInput, origin, '|');
		getline(graphInput, destination, '|');
		graphInput >> time;
		repairInputStream(graphInput);
		graphInput >> cost;

		addRoute(origin, destination, cost, time);
	}
    
	graphInput.close();

	ifstream requestInput(requestInputName);

	if (!requestInput.good())
	{
		return;
	}

	int requestTotal;
	requestInput >> requestTotal;

	bool types[requestTotal] { false };
	LinkedList<SortedList<FlightPlan>> plans;

	for (int i = 0; i < requestTotal; i++)
	{
		repairInputStream(requestInput);
		String origin;
		String destination;
		char type;

		getline(requestInput, origin, '|');
		getline(requestInput, destination, '|');
		requestInput >> type;

		types[i] = type == 'C';
		plans.addElementByValue(getRoutes(origin, destination, types[i]));
	}
    
	requestInput.close();

	ofstream output(outputName);

	if (!output.good())
	{
		return;
	}

	int typeIndex = 0;
    
	for (SortedList<FlightPlan>& planGroup : plans)
	{
		output << "Flight "
				<< (typeIndex + 1)
				<< ": "
				<< planGroup.getElement(0).getOrigin()
				<< ", "
				<< planGroup.getElement(0).getDestination()
				<< " ("
				<< (types[typeIndex] ? "Cost" : "Time")
				<< ")" << endl;

		planGroup.removeElement(0);
		typeIndex++;

		if (planGroup.isEmpty())
		{
			output << "No possible flight path" << endl << endl;
		}
		else
		{
			for (unsigned int i = 0; i < 3 && !planGroup.isEmpty(); i++)
			{
				FlightPlan plan = planGroup.removeElement(0);
				output << "Path " << (i + 1) << ": ";
                
				for (String hop : plan.getHops())
				{
					output << hop;
                    
					if (hop != plan.getDestination())
					{
						output << " -> ";
					}
					else
					{
						output << ". ";
					}
				}
                
				output << "Time: " << plan.getTime() << " Cost: " << plan.getCost() << endl;
			}
            
			output << endl;
		}
	}

	output.close();
}

void FlightPlanner::addRoute(String& pointA, String& pointB, double cost, unsigned int time)
{
	graph[pointA].addElementByValue(FlightData(pointB, cost, time));
	graph[pointB].addElementByValue(FlightData(pointA, cost, time));
}

SortedList<FlightPlan> FlightPlanner::getRoutes(String& pointA, String& pointB, bool cost)
{
	LinkedList<String> previous;
	SortedList<FlightPlan> completed([=](FlightPlan& e1, FlightPlan& e2) -> bool
	{
		if (cost)
		{
			return e1.getCost() < e2.getCost();
		}

		return e1.getTime() < e2.getTime();
	});
    
	completed.addElementByValue(FlightPlan(pointA, pointB));

	Stack<FlightData> routeStack;
	Stack<unsigned int> routeIndexStack;

	routeStack.pushByValue(FlightData(pointA, 0, 0));
	routeIndexStack.pushByValue(0);
    
	while (!routeStack.isEmpty())
	{
		if (routeStack.peek().getDestination() == pointB)
		{
			completed.addElementByValue(FlightPlan(routeStack));
			routeStack.pop();
			routeIndexStack.pop();
            
			if (!routeIndexStack.isEmpty())
			{
				routeIndexStack.peek()++;
			}
            
			if (!previous.isEmpty())
			{
				previous.popBack();
			}
            
			continue;
		}

		LinkedList<FlightData>& destinations = graph[routeStack.peek().getDestination()];

		if (routeIndexStack.peek() >= destinations.getSize() || previous.containsElement(routeStack.peek().getDestination()))
		{
			if (!previous.isEmpty())
			{
				previous.popBack();
			}
            
			routeStack.pop();
			routeIndexStack.pop();
            
			if (!routeIndexStack.isEmpty())
			{
				routeIndexStack.peek()++;
			}
		}
		else
		{
			previous.addElement(routeStack.peek().getDestination());
			routeStack.push(destinations.getElement(routeIndexStack.peek()));
			routeIndexStack.pushByValue(0);
		}
	}

	return completed;
}
