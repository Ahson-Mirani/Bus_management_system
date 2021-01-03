#include"ticket.h"
#include<time.h>

int randomNum(int start, int end);

//======================================================DRIVER===================================================================
void fillNameGender(std::vector < std::string>& DriverName, std::vector <int>& DriverGender);
long long randomCNIC();
driver randomDriver(std::vector < std::string> DriverName, std::vector <int> DriverGender, int index);
void starterDrivers(std::vector<driver>& myDrivers, std::vector < std::string> DriverName, std::vector <int> DriverGender);

//======================================================LOCATION=================================================================
void fillLocationNames(std::vector < std::string>& LocationNames);
location randomLocation(std::vector < std::string> LocationNames, int index);
void starterLocations(std::vector<location>& myLocations, std::vector < std::string> LocationNames);

//======================================================ROUTE=====================================================================
route randomRoute(std::vector<location>& myLocations);
void starterRoutes(std::vector<route>& myRoutes, std::vector<location>& myLocations);

//======================================================BUS=====================================================================
void fillBusNames(std::vector < std::string>& BusNames);
bus randomBus(std::vector<route>& myRoutes, std::vector<driver>& myDrivers, std::vector < std::string>& BusNames);
void starterBuses(std::vector<bus>& myBuses, std::vector<route>& myRoutes, std::vector<driver>& myDrivers, std::vector < std::string>& BusNames);

void loadStarterData(std::vector<bus>& myBuses, std::vector<driver>& myDrivers, std::vector<route>& myRoutes, std::vector<location>& myLocations);