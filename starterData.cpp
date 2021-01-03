#include"starterData.h"

int randomNum(int start, int end){
	return (rand() % end) + start;
}
//===============================================================DRIVER PACKAGE====================================================================
void fillNameGender(std::vector < std::string>& DriverName, std::vector <int>& DriverGender){
	DriverName.push_back(std::string("Ahmed")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Tucker")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Sheldon")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Javed")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Uzair")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Bob")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Raja")); DriverGender.push_back(0);
	DriverName.push_back(std::string("Sara")); DriverGender.push_back(1);
	DriverName.push_back(std::string("Rachel")); DriverGender.push_back(1);
	DriverName.push_back(std::string("Rani")); DriverGender.push_back(1);
}
long long randomCNIC(){
	srand(time(NULL));
	return  (10000000000 * randomNum(0, 9) + 1000000000 * randomNum(0, 9) + 100000000 * randomNum(0, 9) + 10000000 * randomNum(0, 9) +
		1000000 * randomNum(0, 9) + 100000 * randomNum(0, 9) + 10000 * randomNum(0, 9) + 1000 * randomNum(0, 9) + 100 * randomNum(0, 9) +
		10 * randomNum(0, 9) + 1 * randomNum(0, 9));
}
driver randomDriver(std::vector < std::string> DriverName, std::vector <int> DriverGender, int index){
	driver tempDriver;
	tempDriver.name = DriverName[index];
	tempDriver.gender = DriverGender[index];
	tempDriver.age = randomNum(18, 50);
	tempDriver.CNIC = randomCNIC();
	return tempDriver;
}
void starterDrivers(std::vector<driver>& myDrivers, std::vector < std::string> DriverName, std::vector <int> DriverGender){
	for (int i = 0; i < DriverName.size(); i++){
		myDrivers.push_back(randomDriver(DriverName, DriverGender, i));
	}
}

//===============================================================LOCATION PACKAGE====================================================================
void fillLocationNames(std::vector < std::string>& LocationNames){
	LocationNames.push_back(std::string("Sukkur"));
	LocationNames.push_back(std::string("Karachi"));
	LocationNames.push_back(std::string("Hyderabad"));
	LocationNames.push_back(std::string("Lahore"));
	LocationNames.push_back(std::string("Sialkot"));
	LocationNames.push_back(std::string("Dadu"));
	LocationNames.push_back(std::string("Rohri"));
	LocationNames.push_back(std::string("Peshawar"));
	LocationNames.push_back(std::string("Lakhi"));
	LocationNames.push_back(std::string("Quetta"));
	LocationNames.push_back(std::string("Islamabad"));
	LocationNames.push_back(std::string("Pindi"));
	LocationNames.push_back(std::string("Shikarpur"));
	LocationNames.push_back(std::string("Larkana"));
	LocationNames.push_back(std::string("Badin"));
}
location randomLocation(std::vector < std::string> LocationNames, int index){
	location tempLocation;
	tempLocation.name = LocationNames[index];
	tempLocation.x_cod = randomNum(0, 100);
	tempLocation.y_cod = randomNum(0, 100);
	return tempLocation;
}
void starterLocations(std::vector<location>& myLocations, std::vector < std::string> LocationNames){
	for (int i = 0; i < LocationNames.size(); i++){
		myLocations.push_back(randomLocation(LocationNames, i));
	}
}

//===============================================================ROUTE PACKAGE====================================================================
route randomRoute(std::vector<location>& myLocations){
	route tempRoute;
	int indexForDept = randomNum(0, myLocations.size() - 1);
	int indexForDest = randomNum(0, myLocations.size() - 1);
	while (indexForDept == indexForDest){
		indexForDest = randomNum(0, myLocations.size() - 1);
	}
	tempRoute.departureID = myLocations[indexForDept].locationID;
	myLocations[indexForDept].AssignedDeparture.push_back(tempRoute.routeID);
	tempRoute.destinationID = myLocations[indexForDest].locationID;
	myLocations[indexForDest].AssignedDestination.push_back(tempRoute.routeID);
	tempRoute.ratePERkm = randomNum(10, 100);
	tempRoute.updateDistanceFare(myLocations);
	return tempRoute;
}
void starterRoutes(std::vector<route>& myRoutes, std::vector<location>& myLocations){
	for (int i = 0; i < myLocations.size(); i++){
		myRoutes.push_back(randomRoute(myLocations));
	}
}

//===============================================================BUS PACKAGE====================================================================
void fillBusNames(std::vector < std::string>& BusNames){
	BusNames.push_back(std::string("Yutong"));
	BusNames.push_back(std::string("Daewoo"));
	BusNames.push_back(std::string("BluLine"));
	BusNames.push_back(std::string("Luxy"));
	BusNames.push_back(std::string("Royal"));
	BusNames.push_back(std::string("RedLine"));
	BusNames.push_back(std::string("YelloLine"));
	BusNames.push_back(std::string("Fudgy"));
	BusNames.push_back(std::string("Taj"));
	BusNames.push_back(std::string("Naaz"));
	BusNames.push_back(std::string("Buzzy"));
	BusNames.push_back(std::string("Sassy"));
	BusNames.push_back(std::string("DonaDrive"));
}
bus randomBus(std::vector<route>& myRoutes, std::vector<driver>& myDrivers, std::vector < std::string>& BusNames){
	bus tempBus;
	tempBus.busName = BusNames[randomNum(0, BusNames.size() - 1)];
	int index = randomNum(0, myDrivers.size() - 1);
	tempBus.idOfDriverOfBus = myDrivers[index].DriversID;
	myDrivers[index].assignBus(tempBus.BusID);
	index = randomNum(0, myRoutes.size() - 1);
	tempBus.idOfRouteOfBus = myRoutes[index].routeID;
	myRoutes[index].AssignedToBuses.push_back(tempBus.BusID);
	tempBus.fare = myRoutes[index].fare;
	tempBus.totalSeats = randomNum(20, 70);
	tempBus.assignSeatNos();
	date tempDate(randomNum(1, 30), randomNum(1, 12), randomNum(2020, 6));
	tempBus.DepartureDate = tempDate;
	mytime tempTime(randomNum(0, 24), randomNum(0, 60), randomNum(0, 60));
	tempBus.DepartureTime = tempTime;
	return tempBus;
}
void starterBuses(std::vector<bus>& myBuses, std::vector<route>& myRoutes, std::vector<driver>& myDrivers, std::vector < std::string>& BusNames){
	for (int i = 0; i < 100; i++){
		myBuses.push_back(randomBus(myRoutes, myDrivers, BusNames));
	}
}

//===============================================================COMPLETE STARTER PACKAGE===============================================================
void loadStarterData(std::vector<bus>& myBuses, std::vector<driver>& myDrivers, std::vector<route>& myRoutes, std::vector<location>& myLocations){
	//Variables
	std::vector <std::string> DriverName, LocationNames, BusNames;
	std::vector <int> DriverGender;

	//Fill variables
	fillNameGender(DriverName, DriverGender);
	fillLocationNames(LocationNames);
	fillBusNames(BusNames);

	//Load Starter packages
	starterDrivers(myDrivers, DriverName, DriverGender);
	starterLocations(myLocations, LocationNames);
	starterRoutes(myRoutes, myLocations);
	starterBuses(myBuses, myRoutes, myDrivers, BusNames);
}