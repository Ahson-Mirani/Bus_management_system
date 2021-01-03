#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
#include"seat.h"

class location{
protected:
	static int nextID;
public:
	location(){
		locationID = ++nextID;
	}
	std::string name;
	int x_cod, y_cod, locationID;
	//data association
	std::vector<int> AssignedDeparture;//save id of route whom this location is saved as departure location
	std::vector<int> AssignedDestination;//save id of route whom this location is saved as destination location

	//functions
	void setLocation();
	void getDetails(int);
	void update();
};

class route{
protected:
	static int nextID;
public:
	route(){
		routeID = ++nextID;
		departureID = -1; destinationID = -1;//-1 denotes not assigned at the moment
	}
	int routeID;
	int departureID, destinationID;
	double distance, fare, ratePERkm;
	std::vector<int>AssignedToBuses;

	void setDetail(std::vector<location>&);
	void getDetail(std::vector<location>,int);
	void updateDistanceFare(std::vector<location>&);
	void update(std::vector<location>&);
	void setDistanceRoute(std::vector<location>);
};