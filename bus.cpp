#include"bus.h"

int bus::nextId = 0;
int driver::nextId = 0;

void driver::assignBus(int id){
	AssignedBuses.push_back(id);
}

void driver::setDriverDetails(int x, int y){
	locate(x, y); std::cout << "Enter data of driver to hire him...\n";
	locate(x, y + 1); std::cout << "Name:"; std::cin >> name;
	locate(x, y + 2); std::cout << "Gender:"; std::cin >> gender;
	locate(x, y + 3); std::cout << "CNIC:"; std::cin >> CNIC;
	locate(x, y + 4); std::cout << "Age:"; std::cin >> age;
}

void driver::getDriverDetails(int i){
	std::cout << i << ":" << name << "\n";
}

void driver::getTodaysDate(){}

void driver::update(){
	std::string tempName; int tempGender, tempAge; long long tempCNIC;
	printSpaces(15);	std::cout << "Enter new data to Update and -1 to not change prev data:\n";
	printSpaces(15); std::cout << "Update name:"; std::cin >> tempName;
	if (tempName != "-1") name = tempName;
	printSpaces(15);	std::cout << "Update Gender:"; std::cin >> tempGender;
	if (tempGender != -1) gender = tempGender;
	printSpaces(15); std::cout << "Update CNIC:"; std::cin >> tempCNIC;
	if (tempCNIC != -1) CNIC = tempCNIC;
	printSpaces(15); std::cout << "Update Age:"; std::cin >> tempAge;
	if (tempAge != -1) age = tempAge;
}

void bus::assignSeatNos(){
	Seats = new seat[totalSeats];//set seating limit
	for (int i = 0; i < totalSeats; i++){
		Seats[i].seatNo = i + 1;
		Seats[i].setStandard();
	}
}

void bus::listEmptySeats(){
	for (int i = 0; i < totalSeats; i++){
		if (Seats[i].isOccupied == false){
			std::cout << Seats[i].seatNo << " ";
		}
	}
	std::cout << "\n";
}

void bus::getBusDetails(int y, std::vector<driver> d, std::vector<route> r, std::vector<location> l){
	locate(10, y);	std::cout << BusID;
	locate(15, y); std::cout << busName;
	if (idOfDriverOfBus != -1){
		//find driver with the id and print his name
		for (int i = 0; i < d.size(); i++){
			if (d[i].DriversID == idOfDriverOfBus){
				locate(35, y); std::cout << d[i].name;
			}
		}
	}
	else{
		locate(35, y); std::cout << "N/A";
	}
	//find route and print it
	if (idOfRouteOfBus != -1){
		for (int i = 0; i, i<r.size(); i++){
			if (r[i].routeID == idOfRouteOfBus){
				location tempDept, tempDest;
				//this is the route, print it
				for (int j = 0; j < l.size(); j++){
					if (r[i].departureID == l[j].locationID){
						tempDept = l[j];
					}
					if (r[i].destinationID == l[j].locationID){
						tempDest = l[j];

					}
				}
				locate(55, y); std::cout << tempDept.name << " to " << tempDest.name << "\n";
			}
		}
	}
	else{
		locate(55, y);	std::cout << "No route assigned";
	}
	locate(100, y); std::cout << totalSeats;
}


void bus::setBusDetails(std::vector<driver>& d, std::vector<route>& r, std::vector<location>& l){
	char flagAssignDriver;
	bool isDriverAssigned = false;
	int whichDriver;;
	std::cout << "\tBus name:"; std::cin >> busName;
	do{
		locate(0, 2); std::cout << "\tAssign Driver?(y/n):"; std::cin >> flagAssignDriver;
		if (flagAssignDriver == 'y'){
			int existinOrnewDriver;
#define ExistingDriverOption 1
#define NewDriverOption 2
			//Options to add driver
			std::cout << "\t\t1. Assign existing driver\n\t\t2. Hire new driver and Assign\n\tYour choice:"; std::cin >> existinOrnewDriver;
			while (existinOrnewDriver != ExistingDriverOption && existinOrnewDriver != NewDriverOption){
				locate(0, 5); std::cout << "\tYour choice:"; printSpaces(nooOfDigits(existinOrnewDriver)); backSpaces(nooOfDigits(existinOrnewDriver)); std::cin >> existinOrnewDriver;
			}
			if (existinOrnewDriver == ExistingDriverOption){
				//Display all drivers
				if (d.size()){
					for (int i = 0; i < d.size(); i++){
						std::cout << "\t\t" << i + 1 << ": " << d[i].name << "\n";
					}
					std::cout << "\tSelect:"; std::cin >> whichDriver;
					while (whichDriver<0 || whichDriver>d.size()){
						locate(0, 6 + d.size()); std::cout << "\tSelect:"; printSpaces(nooOfDigits(whichDriver)); backSpaces(nooOfDigits(whichDriver)); std::cin >> whichDriver;
					}

					idOfDriverOfBus = d[whichDriver - 1].DriversID;//Driver is assigned :. his id is saved
					d[whichDriver - 1].assignBus(this->BusID);

					//std::cout << "\tDriver is assigned.\n";
					isDriverAssigned = true;
					Sleep(100);
					locate(22, 2); std::cout << "(" << d[whichDriver - 1].name << ")";
					for (int i = (d.size() + 7); i > 2; i--){
						locate(0, i);
						std::cout << "                                                                                                    ";
						Sleep(5);
					}
				}
				else{
					locate(32, 2); std::cout << "(None Added)";
					locate(0, 3); std::cout << "                                                                                                    ";
					locate(0, 4); std::cout << "                                                                                                    ";
					locate(0, 5); std::cout << "                                                                                                    ";
				}
			}
			else{
				//hire new driver
				driver tempDriver;
				tempDriver.setDriverDetails(16,6);

				idOfDriverOfBus = tempDriver.DriversID;//Driver is assigned :. his id is saved
				tempDriver.assignBus(this->BusID);

				d.push_back(tempDriver);	//driver is added in staff
				locate(32, 2); std::cout << "            ";
				locate(22, 2); std::cout << "(" << tempDriver.name << ")";
				for (int i = (3 + 7); i > 2; i--){
					locate(0, i);
					std::cout << "                                                                                                    ";
					Sleep(5);
				}
				isDriverAssigned = true;
			}
		}
	} while (!(flagAssignDriver == 'y' && isDriverAssigned == true) && !(flagAssignDriver == 'n' && isDriverAssigned == false));

	//Select route
	char flagAssignRoute;
	bool isRouteAssigned = false;
	int whichRoute;
	do{
		locate(0, 3); std::cout << "\tAssign Route?(y/n):"; std::cin >> flagAssignRoute;
		if (flagAssignRoute == 'y'){
			//Display all routes
			bool areRoutesDisplayed = false;
			if (r.size()){
				for (int i = 0; i < r.size(); i++){
					if (r[i].departureID != -1 && r[i].destinationID != -1){
						location tempDept, tempDest;
						//print the route
						//find departure and destination cities from locations
						for (int j = 0; j < l.size(); j++){
							if (r[i].departureID == l[j].locationID){
								tempDept = l[j];
							}
							if (r[i].destinationID == l[j].locationID){
								tempDest = l[j];

							}
						}
						std::cout << "\t\t\t" << i + 1 << ":" << tempDept.name << " to " << tempDest.name << "\n";
						areRoutesDisplayed = true;
					}
				}
				if (areRoutesDisplayed){
					locate(0, 4 + r.size()); std::cout << "\tSelect:"; std::cin >> whichRoute;
					while (whichRoute<0 || whichRoute>r.size()){
						locate(0, 4 + r.size()); std::cout << "\tSelect:"; printSpaces(nooOfDigits(whichRoute)); backSpaces(nooOfDigits(whichRoute)); std::cin >> whichRoute;
					}

					idOfRouteOfBus = r[whichRoute - 1].routeID;//route is assigned :. its id is saved
					r[whichRoute - 1].AssignedToBuses.push_back(this->BusID);

					Sleep(100);
					locate(21, 3);
					std::cout << "(" << l[getLocation(l, r[whichRoute - 1].departureID)].name << " to " << l[getLocation(l, r[whichRoute - 1].destinationID)].name << ")";
					for (int i = (r.size() + 9); i > 3; i--){
						locate(0, i);
						std::cout << "                                                                                                    ";
						Sleep(5);
					};
					isRouteAssigned = true;
				}
				else{
					locate(30, 3); std::cout << "(None active)";
					locate(0, 4); std::cout << "                                                                                                    ";
					locate(0, 5); std::cout << "                                                                                                    ";
					locate(0, 6); std::cout << "                                                                                                    ";
					isRouteAssigned = true;
					//move back to option to choose for how to assign route
				}
			}//if(r.size()
			else{
				locate(30, 3); std::cout << "(None added)\n";
				locate(0, 4); std::cout << "                                                                                                    ";
				locate(0, 5); std::cout << "                                                                                                    ";
				locate(0, 6); std::cout << "                                                                                                    ";
				//move back to option to choose for how to assign route
			}
		}//if(flag assigned true) 
		//matter of Route is settled
	} while (!(flagAssignRoute == 'y' && isRouteAssigned == true) && !(flagAssignRoute == 'n' && isRouteAssigned == false));

	int tempSeatingLimit;
	locate(0, 4); std::cout << "\tDefault seats:" << totalSeats << "\n\tEnter new value to change it(0 for default):"; std::cin >> tempSeatingLimit;
	
	while (tempSeatingLimit < 0){
		locate(0, 6); std::cout << "\tInvalid...Enter new value to change it(0 for default):"; std::cin >> tempSeatingLimit;
	}
	if (tempSeatingLimit != 0){
		totalSeats = tempSeatingLimit;
		assignSeatNos();
	}


	//set departure date and time
	std::cout << "\tDeparture Date:\n";
	DepartureDate.setdate();
	//collapse Date
	locate(0, 9); 			std::cout << "                                                                                                    ";
	locate(0, 8);			std::cout << "                                                                                                    ";
	locate(0, 7);			std::cout << "                                                                                                    ";
	locate(23, 6);			std::cout << DepartureDate;
	locate(0, 7); std::cout << "\tDeparture Time:\n";
	DepartureTime.setTime();
	//collapse Time
	locate(0, 10); 			std::cout << "                                                                                                    ";
	locate(0, 9);			std::cout << "                                                                                                    ";
	locate(0, 8);			std::cout << "                                                                                                    ";
	locate(23, 7);			std::cout << DepartureTime;
	//All details of bus are set
}

void bus::update(std::vector<driver>& myDrivers, std::vector<route>& myRoutes, std::vector<location>& myLocations){
	std::string tempName, updateDriver, updateRoute;
	int tempSeatLimit;
	//update name
	std::cout << "\t\tUpdate name:(-1 to not change):"; std::cin >> tempName;
	if (tempName != "-1") busName = tempName;
	//update driver
	locate(0, 4); std::cout << "\t\tUpdate Driver(y/n):"; std::cin >> updateDriver;
	while (updateDriver != "n" && updateDriver != "N" && updateDriver != "y" && updateDriver != "Y"){
		locate(0, 4); std::cout << "\t\tUpdate Driver(y/n):"; std::cin >> updateDriver;
	}
	if (updateDriver != "n" && updateDriver != "N"){
		//remove this bus from the previous driver's assigned to buses list
		if (idOfDriverOfBus != -1){
			for (int i = 0; i < myDrivers.size(); i++){
				if (idOfDriverOfBus = myDrivers[i].DriversID){
					for (int j = 0; j < myDrivers[i].AssignedBuses.size(); j++){
						if (myDrivers[i].AssignedBuses[j] == BusID){
							myDrivers[i].AssignedBuses.erase(myDrivers[i].AssignedBuses.begin() + j);
						}
					}
				}
			}
		}
		//change driver of this bus
		if (myDrivers.size()){
			int whichDriver;
			//Add driver from list
			for (int i = 0; i < myDrivers.size(); i++){
				std::cout << "\t\t\t" << i + 1 << ")" << myDrivers[i].name << "\n";
			}
			std::cout << "\t\tWhich driver:"; std::cin >> whichDriver;
			while (whichDriver<1 || whichDriver>myDrivers.size()){
				locate(0, 5 + myDrivers.size()); std::cout << "\t\tWhich driver:"; std::cin >> whichDriver;
			}
			//assign this driver to this bus
			idOfDriverOfBus = myDrivers[whichDriver - 1].DriversID;

			myDrivers[whichDriver - 1].assignBus(BusID);
			//collapse drivers
			for (int i = 5 + myDrivers.size(); i > 4; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
			locate(35, 4); std::cout << "(" << myDrivers[whichDriver - 1].name << ")";
		}
		else{
			locate(35, 4); std::cout << "(None Added)";
		}
	}
	//update route
	locate(0, 5); std::cout << "\t\tUpdate Route(y/n):"; std::cin >> updateRoute;
	while (updateRoute != "n" && updateRoute != "N" && updateRoute != "y" && updateRoute != "Y"){
		locate(0, 5); std::cout << "\t\tUpdate Route(y/n):"; std::cin >> updateRoute;
	}
	if (updateRoute != "n" && updateRoute != "N"){
		//do some stuff with prev route if any
		if (idOfRouteOfBus != -1){
			//remove this bus from the assigned to buses list of the prev route
			for (int i = 0; i < myRoutes.size(); i++){
				if (idOfRouteOfBus == myRoutes[i].routeID){
					for (int j = 0; j < myRoutes[i].AssignedToBuses.size(); j++){
						if (myRoutes[i].AssignedToBuses[j] == BusID){
							myRoutes[i].AssignedToBuses.erase(myRoutes[i].AssignedToBuses.begin() + j);
						}
					}
				}
			}
		}
		bool isRouteUpdated = false;
		//change route of this bus
		int whichRoute, methodRoute;
		if (myRoutes.size()){
			bool areRoutesDisplayed = false;
			//Add route from list
			for (int i = 0; i < myRoutes.size(); i++){
				if (myRoutes[i].departureID != -1 && myRoutes[i].destinationID != -1){
					location tempDept, tempDest;
					//print the route
					//find departure city from locations
					//find destination city from locations
					for (int j = 0; j < myLocations.size(); j++){
						if (myRoutes[i].departureID == myLocations[j].locationID){
							tempDept = myLocations[j];
						}
						if (myRoutes[i].destinationID == myLocations[j].locationID){
							tempDest = myLocations[j];
						}
					}
					std::cout <<"\t\t\t"<< i + 1 << ":" << tempDept.name << " to " << tempDest.name << "\n";
					areRoutesDisplayed = true;
				}
			}
			if (areRoutesDisplayed){
				std::cout << "\t\tWhich route:"; std::cin >> whichRoute;
				while (whichRoute<1 || whichRoute>myRoutes.size()){
					locate(0, 6 + myRoutes.size()); std::cout << "\t\tWhich route:"; printSpaces(nooOfDigits(whichRoute)); backSpaces(nooOfDigits(whichRoute)); std::cin >> whichRoute;
				}
				//assign this route to this bus
				idOfRouteOfBus = myRoutes[whichRoute - 1].routeID;

				myRoutes[whichRoute - 1].AssignedToBuses.push_back(BusID);
				isRouteUpdated = true;
				//collapse route
				for (int i = 6 + myRoutes.size(); i > 5; i--){
					locate(0, i); std::cout << "                                                                                                    ";
				}
				locate(34, 5); std::cout << "(" << myLocations[getLocation(myLocations, myRoutes[whichRoute - 1].departureID)].name << " to " << myLocations[getLocation(myLocations, myRoutes[whichRoute - 1].destinationID)].name << ")";
			}
			else{
				locate(34, 5); std::cout << "(None active)";
			}
		}
		else{
			locate(34, 5); std::cout << "(None added)";
		}
	}
	//update seating limit
	locate(0, 6); std::cout << "\t\tUpdate Seating Limit(-1 to not change):"; std::cin >> tempSeatLimit;
	while (tempSeatLimit < -1 || tempSeatLimit == 0){
		locate(0, 6); std::cout << "\t\tUpdate Seating Limit(-1 to not change):"; printSpaces(nooOfDigits(tempSeatLimit)); backSpaces(nooOfDigits(tempSeatLimit)); std::cin >> tempSeatLimit;
	}
	if (tempSeatLimit != -1){
		totalSeats = tempSeatLimit;
		assignSeatNos();
	}
}

int bus::getLocation(std::vector<location>myLocations, int ID){
	for (int i = 0; i < myLocations.size(); i++){
		if (myLocations[i].locationID == ID)return i;
	}
	return -1;
}

int bus::getRoute(std::vector<route>myRoutes){
	for (int i = 0; i < myRoutes.size(); i++){
		if (myRoutes[i].routeID == idOfRouteOfBus) return i;
	}
	return -1;
}

void bus::displayForBooking(std::vector<location>myLocations, std::vector<route>myRoutes, int y){
	std::string departure, destination;
	if (getRoute(myRoutes) != -1){
		locate(110, y); std::cout << myRoutes[getRoute(myRoutes)].fare;
		if (getLocation(myLocations, myRoutes[getRoute(myRoutes)].departureID) != -1){
			locate(15, y); std::cout << myLocations[getLocation(myLocations, myRoutes[getRoute(myRoutes)].departureID)].name;
		}
		else{
			locate(15, y); std::cout << "N/A";
		}
		if (getLocation(myLocations, myRoutes[getRoute(myRoutes)].destinationID) != -1){
			locate(40, y); std::cout << myLocations[getLocation(myLocations, myRoutes[getRoute(myRoutes)].destinationID)].name;
		}
		else{
			locate(40, y); std::cout << "N/A";
		}
	}
	else{
		locate(15, y); std::cout << "N/A";
		locate(40, y); std::cout << "N/A";
		locate(110, y); std::cout << "N/A";
	}

	locate(5, y); std::cout << busName;				locate(65, y); std::cout << totalSeats;
	locate(85, y); std::cout << DepartureDate;		locate(100, y); std::cout << DepartureTime;
}

bool bus::isAvailabe(){
	if (idOfDriverOfBus != -1 && idOfRouteOfBus != -1) return true;
	return false;
}

std::vector<int> bus::booking(){
	std::vector<int>bookedSeats;
	bool exit = false;
	int anotherBooking, bookSeatNo;;
	do{
		listEmptySeats();
		std::cout << "Enter seat number:"; std::cin >> bookSeatNo;
		//check if seat is valid and not occupied
		while (bookSeatNo <= 0 && bookSeatNo > totalSeats){
			std::cout << "Invalid seat no, please enter valid seat:";
			std::cin >> bookSeatNo;
		}
		if (Seats[bookSeatNo - 1].isOccupied){
			std::cout << "This seat is already occupied...";
		}
		else{
			Seats[bookSeatNo - 1].book();
			bookedSeats.push_back(Seats[bookSeatNo - 1].seatNo);
			//			viewMydetails(bookSeatNo);
		}
		std::cout << "Book another seat from this bus(1/0)"; std::cin >> anotherBooking;
		while (anotherBooking != 1 && anotherBooking != 0){
			std::cout << "Wrong choice...choose again:"; std::cin >> anotherBooking;
		}
		if (!anotherBooking) exit = true;
	} while (!exit);
	return bookedSeats;
}

void bus::detailedPage(std::vector<driver> d, std::vector<route> r, std::vector<location> l){
	int seatOption;
	do{
		system("cls");
		locate(55, 0); std::cout << "DETAILED PAGE OF BUS\n";
		std::cout << "\tBus Id:" << BusID << "\n";
		std::cout << "\tBus Name:" << busName << "\n\n";
		if (idOfDriverOfBus != -1){
			//find driver with the id and print his name
			for (int i = 0; i < d.size(); i++){
				if (d[i].DriversID == idOfDriverOfBus){
					std::cout << "\tDriver name:" << d[i].name << "\n\n";
				}
			}
		}
		else{
			std::cout << "\tDriver name:N/A\n\n";
		}
		std::cout << "\tNumber of seats:" << totalSeats << "\n\n";
		if (idOfRouteOfBus != -1){
			//find route assigned to this bus
			for (int i = 0; i < r.size(); i++){
				if (idOfRouteOfBus == r[i].routeID){
					//this is the route assigned to this bus
					std::cout << "\tDeparture city:" << l[getLocation(l,r[i].departureID)].name << "\n";
					std::cout << "\tDestination city:" << l[getLocation(l, r[i].destinationID)].name << "\n";
					std::cout << "\tFare: " << r[i].fare << "\n\n";
					}
				}
			}
		else{
			std::cout << "\tDeparture city:N/A\n";
			std::cout << "\tDestination city:N/A\n";
			std::cout << "\tFare: N/A\n\n";
		}
		std::cout << "\tDeparture date:" << DepartureDate << "\n";
		std::cout << "\tDeparture time:" << DepartureTime << "\n";
		printVisual();
		
		locate(15, 16); std::cout << "\n\tView Seat(0 to exit):"; std::cin >> seatOption;
		while (seatOption<0 && seatOption>totalSeats){
			std::cout << "Wrong choice...Select again:";
		}
		if (seatOption != 0){ system("cls"); Seats[seatOption - 1].printDetails();	std::cout << "\t"; system("pause"); }
	} while (seatOption != 0);
}

void driver::detailedPage(){
	system("cls");
	locate(55, 0); std::cout << "DETAILED PAGE OF DRIVER...\n";
	printSpaces(15); std::cout << "Id of Driver:" << DriversID << "\n\n";
	printPerson(15); std::cout << "\n";
	for (int i = 0; i < AssignedBuses.size(); i++){
		printSpaces(15); std::cout << "Bus assigned:" << AssignedBuses[i] << "\n";
	}
	printSpaces(15); system("pause");
}

void bus::viewSeatDetails(int seatNo){
	Seats[seatNo].printDetails();
}


//locate function
HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void locate(int x, int y){
	COORD c;
	c.X = x; c.Y = y;
	SetConsoleCursorPosition(myConsole, c);
}

void bus::printVisual(){//HOPING TO DESIGN THIS FUNCTION TO DISPLAY VISUAL BUS
	int count = 0;
	for (int i = 1; i <= totalSeats / 4; i++){
		for (int j = 1; j <= 5; j++){
			if (j != 3){
				count++;
				if (Seats[count - 1].isOccupied){
					SetConsoleTextAttribute(myConsole, 12);
					locate(75 + 4 * j, 4 + i);
					std::cout << count;
				}
				else{
					SetConsoleTextAttribute(myConsole, 10);
					locate(75 + 4 * j, 4 + i);
					std::cout << count;
				}
				SetConsoleTextAttribute(myConsole, 7);
			}
		}
	}
}