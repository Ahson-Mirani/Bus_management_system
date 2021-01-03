#include"route.h"

class driver :public person{
	date todaysDate;
protected:
	static int nextId;
public:
	driver(){
		getTodaysDate();
		DriversID = ++nextId;
	}
	int DriversID;
	std::vector<int>AssignedBuses;	//store ids of assigned buses
	date jobStartingDate;
	double serviceYears;

	//functions
	void update();
	double getserviceYears();
	void getTodaysDate();
	void setDriverDetails(int, int);
	void getDriverDetails(int);
	void detailedPage();
	void assignBus(int id);
};

class bus{
	void listEmptySeats();
protected:
	static int nextId;
public:
	bus(){
		//initiate seat no's
		assignSeatNos();
		//assign id
		BusID = ++nextId;
		idOfDriverOfBus = -1;
		idOfRouteOfBus = -1;
	}
	int BusID;
	int totalSeats = 40;
	int idOfDriverOfBus;
	int idOfRouteOfBus;
	seat *Seats;
	std::string busName;

	date DepartureDate;
	mytime DepartureTime;
	double fare;

	std::string departureCity;
	std::string DestinationCity;

	void getBusDetails(int, std::vector<driver>, std::vector<route>, std::vector<location>);
	void setBusDetails(std::vector<driver>&, std::vector<route>&, std::vector<location>&);
	void detailedPage(std::vector<driver>, std::vector<route>, std::vector<location>);
	void update(std::vector<driver>&, std::vector<route>&, std::vector<location>&);
	int getLocation(std::vector<location>, int);
	int getRoute(std::vector<route>);
	void displayForBooking(std::vector<location>, std::vector<route>, int);
	std::vector<int> booking();
	void assignSeatNos();
	void printVisual();
	void viewSeatDetails(int seatNo);
	bool isAvailabe();
};

//Populate more options for vehicle types
class miniVan :public bus{

};