#include"functions.h"
using namespace std;

#define adminAccount 1
#define generalAccount 2
#define exit 3


int chooseAccountType(){
	string username, password;
	int signinOption;
	system("cls");
	locate(55, 0); cout << "LOGIN PAGE";
	locate(40, 2); cout << "Sign in as:";
	locate(50, 3); cout << "1:Admin";
	locate(50, 5); cout << "2:General";
	locate(50, 7); cout << "3:Exit";
	locate(50, 9); cout << "Choose sign in option:"; cin >> signinOption;
	while (signinOption != adminAccount && signinOption != generalAccount && signinOption != exit){ locate(50, 9); cout << "Choose sign in option:"; printSpaces(nooOfDigits(signinOption)); backSpaces(nooOfDigits(signinOption)); cin >> signinOption; }
	if (signinOption == adminAccount){
		for (int x = 30; x < 80; x++){ locate(x, 11); cout << "*"; }Sleep(100);
		for (int x = 30; x < 80; x++){ locate(x, 17); cout << "*"; }Sleep(200);
		locate(45, 13); cout << "Username:";
		locate(45, 15); cout << "Password:";
		locate(54, 13); cin >> username;
		while (username != "admin"){
			locate(45, 13); cout << "Username:";
			cin >> username;
		}
		locate(54, 15); cin >> password;
		while (password != "secret"){
			locate(45, 15); cout << "Password:";
			cin >> password;
		}
		locate(65, 18); cout << "Logging in"; Sleep(700); cout << ". "; Sleep(700); cout << ". "; Sleep(700); cout << "."; Sleep(500);
		return 1;//admin is logged in
	}
	if (signinOption != exit){ locate(58, 11); cout << "Logging in"; Sleep(700); cout << ". "; Sleep(700); cout << ". "; Sleep(700); cout << "."; Sleep(500);  return 2; }// general user is logged in
	return 3; //exit the program
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////ADMIN CONTROLS START HERE///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void adminMenu(){
	locate(20, 5); cout << "1. Add new bus";
	locate(20, 7); cout << "2. List all buses";
	locate(20, 9); cout << "3. Search bus";
	locate(20, 11); cout << "4. Update details of bus";
	locate(20, 13); cout << "5. Delete bus";
	locate(20, 15); cout << "6. Manage routes";
	locate(20, 17); cout << "7. Manage Drivers";
	locate(20, 19); cout << "8. log out\n";
}
///////////////////////////////////////////////////////////////////////BUSES

void newBus(vector<bus>& myBuses, vector<driver>& myDrivers, vector<route>& myRoutes, vector<location>& myLocations){
	system("cls");
	bus *tempBus = new bus;
	locate(55, 0); cout << "ADD BUS\n";
	tempBus->setBusDetails(myDrivers, myRoutes, myLocations);
	myBuses.push_back(*tempBus);
	cout << "\n\n\tBus is added.\n\t";
	system("pause");
}

void listBuses(vector<bus> myBuses, vector<driver> myDrivers, vector<route> myRoutes, vector<location> mylocations){
	int selectedBus;
	do{
		system("cls");
		locate(55, 0); cout << "LIST OF BUSES";
		locate(0, 2);  cout << "BUS NO   ID\t";
		locate(15, 2); cout << "BUS NAME\t";
		locate(35, 2); cout << "DRIVER NAME\t";
		locate(55, 2); cout << "ROUTE\t";
		locate(100, 2); cout << "NO OF SEATS\n";
		if (myBuses.size()){
			for (int i = 0; i < myBuses.size(); i++){
				locate(0, i + 4); cout << i + 1 << ")";
				myBuses[i].getBusDetails(i + 4, myDrivers, myRoutes, mylocations);
			}
			//Select Bus to see details of driver or seats
			//Aadmin Can change the details from here too...
			cout << "\n\nSelect bus to view its details(0 to exit):"; cin >> selectedBus;
			while (selectedBus<0 || selectedBus>myBuses.size()){
				cout << "Wrong choice..Select again:"; cin >> selectedBus;
			}
			//goto bus's detailed page
			if (selectedBus != 0) myBuses[selectedBus - 1].detailedPage(myDrivers, myRoutes, mylocations);
		}
		else{
			cout << "\n"; printSpaces(55); cout << "NO BUSES ADDED!!!!!\n\n";
			system("pause");
			selectedBus = 0;
		}
	} while (selectedBus != 0);
}
vector<bus> search(int BusID, vector<bus> myBuses){
	vector<bus> temp;
	if (myBuses.size()){
		for (int i = 0; i < myBuses.size(); i++){
			if (BusID == myBuses[i].BusID){
				temp.push_back(myBuses[i]);
			}
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<bus> search(string BusName, vector<bus> myBuses){
	vector<bus> temp;
	if (myBuses.size()){
		for (int i = 0; i < myBuses.size(); i++){
			if (BusName == myBuses[i].busName){
				temp.push_back(myBuses[i]);
			}
		}
		return temp;
	}
	else{
		return temp;;
	}
}

vector<bus> search(route r, vector<bus> myBuses){
	vector<bus> temp;
	if (myBuses.size()){
		for (int i = 0; i < myBuses.size(); i++){
			if (r.routeID == myBuses[i].idOfRouteOfBus){
				temp.push_back(myBuses[i]);
			}
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<bus> search(driver d, vector<bus> myBuses){
	vector<bus> temp;
	if (myBuses.size()){
		for (int i = 0; i < myBuses.size(); i++){
			if (d.DriversID == myBuses[i].idOfDriverOfBus){
				temp.push_back(myBuses[i]);
			}
		}
		return temp;
	}
	else{
		return temp;
	}
}


void searchBus(vector<bus>& myBuses, vector<driver>& myDrivers, vector<route>& myRoutes, vector<location>& myLocations){
	if (myBuses.size()){
		//search a bus
		int searchBusMenuOption;
		do{
			system("cls");
			int busID = 0; string busName = ""; vector<bus>resultBuses; bool noneFound = false;
			//menu for how to search bus/buses
			locate(55, 0); cout << "SEARCH BUS\n";
			cout << "\t1. Search through BusId\n\n";
			cout << "\t2. Search through BusName\n\n";
			cout << "\t3. Search through Driver\n\n";
			cout << "\t4. Search through Route\n\n";
			cout << "\t5. Exit search page\n\n";
			cout << "\tYour choice:"; cin >> searchBusMenuOption;
			while (searchBusMenuOption <= 0 || searchBusMenuOption > 5){
				locate(0, 11); cout << "\tYour choice:"; printSpaces(nooOfDigits(searchBusMenuOption)); backSpaces(nooOfDigits(searchBusMenuOption)); cin >> searchBusMenuOption;
			}
			switch (searchBusMenuOption){
			case 1:	//BusID
				cout << "\tEnter busID to search: "; cin >> busID;
				resultBuses = search(busID, myBuses);
				if (!resultBuses.size())noneFound = true;
				break;
			case 2: //BusName
				cout << "\tEnter busName to search: "; cin >> busName;
				resultBuses = search(busName, myBuses);
				if (!resultBuses.size())noneFound = true;
				break;
			case 3:	//Driver
				int whichDriver;
				//display all drivers first
				if (myDrivers.size()){
					for (int j = 0; j < myDrivers.size(); j++){
						cout <<"\t\t"<< j + 1 << ")" << myDrivers[j].name << "\n";
					}
					cout << "\tSelect Driver:"; cin >> whichDriver;
					while (whichDriver < 1 || whichDriver>myDrivers.size()){
						locate(0, 12 + myDrivers.size()); cout << "\tSelect Driver:"; printSpaces(nooOfDigits(whichDriver)); backSpaces(nooOfDigits(whichDriver)); cin >> whichDriver;
					}
					resultBuses = search(myDrivers[whichDriver - 1], myBuses);
					if (!resultBuses.size())noneFound = true;
				}
				else{
					cout << "\tNo drivers added, so none of the bus have driver...\n\t";
					noneFound = false;
				}
				break;
			case 4:	//route
				int whichRoute;
				//display all routes first
				if (myRoutes.size()){
					for (int j = 0; j < myRoutes.size(); j++){
						location tempDept, tempDest;
						for (int k = 0; k < myLocations.size(); k++){
							if (myRoutes[j].departureID == myLocations[k].locationID){
								tempDept = myLocations[k];
							}
							if (myRoutes[j].destinationID == myLocations[k].locationID){
								tempDest = myLocations[k];

							}
						}
						cout << "\t\t" << j + 1 << ")" << tempDept.name << " to " << tempDest.name << "\n";
					}
					cout << "\tSelect Route:"; cin >> whichRoute;
					while (whichRoute < 1 || whichRoute>myRoutes.size()){
						locate(0, 12 + myRoutes.size()); cout << "\tSelect Route:"; printSpaces(nooOfDigits(whichRoute)); backSpaces(nooOfDigits(whichRoute)); cin >> whichRoute;
					}
					resultBuses = search(myRoutes[whichRoute - 1], myBuses);
					if (!resultBuses.size())noneFound = true;
				}
				else{
					cout << "\tNo routes added, so none of the bus have any route assigned...\n\t";
					noneFound = false;
				}
				break;
			case 5://exit
				break;
			}
			if (searchBusMenuOption != 5){
				if (resultBuses.size())	listBuses(resultBuses, myDrivers, myRoutes, myLocations);
				else{
					if (noneFound)	cout << "\n\tNo bus was found with this data...\n\t";
					system("pause");
				}
			}
		} while (searchBusMenuOption != 5);
	}
	else{
		cout << "\t\tNothing to search, no bus added...:'(\n\t\t";
		system("pause");
	}
}

void updateBus(vector<bus>& myBuses, vector<driver>& myDrivers, vector<route>& myRoutes, vector<location>& myLocations){
	int idToUpdate = 0;
	system("cls");
	locate(55, 0); cout << "UPDATE BUS\n\n";
	do{
		//find the Bus and update its data
		if (myBuses.size()){
			locate(0, 2); cout << "\t\tEnter id of the Bus to update(0 to exit):"; cin >> idToUpdate;
			if (idToUpdate){
				for (int i = 0; i < myBuses.size(); i++){
					if (idToUpdate == myBuses[i].BusID){
						myBuses[i].update(myDrivers, myRoutes, myLocations);
						cout << "\t\tBus's detail is updated...\n\t\t";
						idToUpdate = 0;
						system("pause");
					}
				}
			}
		}
		else{
			cout << "\t\tNoting to update...no Bus added...:'(\n\t\t";
			system("pause");
		}
	} while (idToUpdate != 0);
}

void deleteBus(vector<bus>& myBuses, vector<driver>& myDrivers, vector<route>& myRoutes){
	if (myBuses.size()){
		int DelBus;
		cout << "\t\tEnter busNo to delete Bus:";	cin >> DelBus;
		while (DelBus <= 0 || DelBus > myBuses.size()){
			cout << "\t\tWrong BusNo..Enter again:"; cin >> DelBus;
		}
		if (myBuses[DelBus - 1].idOfDriverOfBus != -1){
			//before removing bus delete id from the driver's assigned buses list
			for (int i = 0; i < myDrivers.size(); i++){
				if (myDrivers[i].DriversID == myBuses[DelBus - 1].idOfDriverOfBus){
					//this driver has the bus assigned, remove thia bus from his assigned bus list
					for (int j = 0; j < myDrivers[i].AssignedBuses.size(); j++){
						//loop thorugh all his assigned bus and find this one to remove
						if (myDrivers[i].AssignedBuses[j] == myBuses[DelBus - 1].BusID){
							//this is the bus, remove this bus from his list
							myDrivers[i].AssignedBuses.erase(myDrivers[i].AssignedBuses.begin() + j);
						}
					}
				}
			}
		}
		//before removing bus delete id of bus from the route's assigned to buses list
		//find the route which is assigned to this bus
		for (int i = 0; i < myRoutes.size(); i++){
			if (myBuses[DelBus - 1].idOfRouteOfBus == myRoutes[i].routeID){
				//this is the route
				for (int j = 0; j < myRoutes[i].AssignedToBuses.size(); j++){
					if (myRoutes[i].AssignedToBuses[j] == myBuses[DelBus - 1].BusID){
						myRoutes[i].AssignedToBuses.erase(myRoutes[i].AssignedToBuses.begin() + j);
					}
				}
			}
		}
		//now delete the bus
		myBuses.erase(myBuses.begin() + DelBus - 1);
		cout << "\t\tBus is deleted.\n\t\t";
	}
	else{
		cout << "\t\tNo buses added yet...Nothing to delete :'(\n\t\t";
	}
	system("pause");
}

///////////////////////////////////////////////////////////////////////LOCATION MANAGEMENT

void AddLocation(vector<location>& myLocations){
	location tempLocation;
	tempLocation.setLocation();
	myLocations.push_back(tempLocation);
	cout << "\t\tLocation is created and added in collection..\n\t\t";
	system("pause");
}

void ListLocations(vector<location> myLocations){
	system("cls");
	locate(55, 0); cout << "LIST OF LOCATIONS\n\n";
	for (int i = 0; i < myLocations.size(); i++){
		myLocations[i].getDetails(i+1);
		cout << "\n\n";
	}
	printSpaces(15); system("pause");
}

vector<location> search(int locationID, vector<location> myLocations){
	vector<location> temp;
	if (myLocations.size()){
		for (int i = 0; i < myLocations.size(); i++){
			if (locationID == myLocations[i].locationID) temp.push_back(myLocations[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<location> search(string locationName, vector<location> myLocations){
	vector<location> temp;
	if (myLocations.size()){
		for (int i = 0; i < myLocations.size(); i++){
			if (locationName == myLocations[i].name) temp.push_back(myLocations[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

void SearchLocation(vector<location> myLocations){
	if (myLocations.size()){
		//search a location
		int searchLocationMenuOption;
		do{
			system("cls");
			locate(55, 0); cout << "SEARCH LOCATION";
			int LocationID = 0; string LocationName = ""; vector<location>resultLocations; bool noneFound = false;
			//menu for how to search location/locations
			locate(15, 2); cout << "1. Search through LocationId\n";
			locate(15, 4); cout << "2. Search through LocationName\n";
			locate(15, 6); cout << "3. Exit search page\n";
			locate(15, 8); cout << "Your choice:"; cin >> searchLocationMenuOption;
			while (searchLocationMenuOption <= 0 || searchLocationMenuOption > 3){
				locate(15, 8); cout << "Your choice:"; printSpaces(nooOfDigits(searchLocationMenuOption)); backSpaces(nooOfDigits(searchLocationMenuOption)); cin >> searchLocationMenuOption;
			}
			switch (searchLocationMenuOption){
			case 1:	//LocationID
				printSpaces(15); cout << "Enter LocationID to search: "; cin >> LocationID;
				resultLocations = search(LocationID, myLocations);
				if (!resultLocations.size()) noneFound = true;
				break;
			case 2: //LocationName
				printSpaces(15); cout << "Enter LocationName to search: "; cin >> LocationName;
				resultLocations = search(LocationName, myLocations);
				if (!resultLocations.size())noneFound = true;
				break;
			case 3:	//Exit
				break;
			}
			if (searchLocationMenuOption != 3){
				if (resultLocations.size())	ListLocations(resultLocations);
				else{
					if (noneFound){ printSpaces(15); cout << "No Location was found with this data...\n"; }
					printSpaces(15); system("pause");
				}
			}
		} while (searchLocationMenuOption != 3);
	}
	else{
		printSpaces(15); cout << "Nothing to search, no Location added...:'(\n";
		printSpaces(15); system("pause");
	}
}

void UpdateLocation(vector<location>& myLocations){
	int idToUpdate = 0;
	do{
		//find the location and update its data
		if (myLocations.size()){
			locate(15, 14); cout << "Enter id of the location to update(0 to exit):"; printSpaces(nooOfDigits(idToUpdate)); backSpaces(nooOfDigits(idToUpdate)); cin >> idToUpdate;
			if (idToUpdate){
				for (int i = 0; i < myLocations.size(); i++){
					if (idToUpdate == myLocations[i].locationID){
						myLocations[i].update();
						printSpaces(15); cout << "Location's detail is updated...\n";
						idToUpdate = 0;
						printSpaces(15); system("pause");
					}
				}
			}
		}
		else{
			printSpaces(15); cout << "Noting to update...no location added...:'(\n";
			printSpaces(15); system("pause");
		}
	} while (idToUpdate != 0);
}

void RemoveLocation(vector<location>& myLocations, vector<route>& myRoutes, vector<bus>& myBuses){
	if (myLocations.size()){
		int DelLocation;

		locate(15, 14); cout << "Enter Location No to delete:";	cin >> DelLocation;
		while (DelLocation <= 0 || DelLocation > myLocations.size()){
			locate(15, 14); cout << "Enter Location No to delete:"; printSpaces(nooOfDigits(DelLocation)); backSpaces(nooOfDigits(DelLocation)); cin >> DelLocation;
		}

		for (int i = 0; i < myRoutes.size(); i++){
			//loop through all routes and find one which has departure location which is now about to be deleted
			if (myRoutes[i].departureID == myLocations[DelLocation - 1].locationID){
				//this route has the location as departure location
				//remove id of this location from the route
				myRoutes[i].departureID = -1;
				myRoutes[i].updateDistanceFare(myLocations);
				//update the details of bus whom this route is assigned
				//loop through all buses and find which bus has this route
				for (int j = 0; j < myBuses.size(); j++){
					if (myRoutes[i].routeID == myBuses[j].idOfRouteOfBus){
						//this bus has this route assigned
						myBuses[j].idOfRouteOfBus = -1;
						//remove this bus from the routes id of Assigned buses
						for (int k = 0; k < myRoutes[i].AssignedToBuses.size(); k++){
							if (myRoutes[i].AssignedToBuses[k] == myBuses[j].BusID){
								myRoutes[i].AssignedToBuses.erase(myRoutes[i].AssignedToBuses.begin() + k);
							}
						}
					}
				}
			}
			if (myRoutes[i].destinationID == myLocations[DelLocation - 1].locationID){
				//this route has the location as destination location
				//remove id of this location from the route
				myRoutes[i].destinationID = -1;
				myRoutes[i].updateDistanceFare(myLocations);
				//update the details of bus whom this route is assigned
				//loop through all buses and find which bus has this route
				for (int j = 0; j < myBuses.size(); j++){
					if (myRoutes[i].routeID == myBuses[j].idOfRouteOfBus){
						//this bus has this route assigned
						myBuses[j].idOfRouteOfBus = -1;
						//remove this bus from the routes id of Assigned buses
						for (int k = 0; k < myRoutes[i].AssignedToBuses.size(); k++){
							if (myRoutes[i].AssignedToBuses[k] == myBuses[j].BusID){
								myRoutes[i].AssignedToBuses.erase(myRoutes[i].AssignedToBuses.begin() + k);
							}
						}
					}
				}
			}
		}
		//delete the location
		myLocations.erase(myLocations.begin() + DelLocation - 1);
		printSpaces(15); cout << "Location is deleted.\n";
	}
	else{
		printSpaces(15); cout << "No buses added yet...Nothing to delete :'(\n";
	}
	printSpaces(15); system("pause");
}

void managelocations(vector<location>& myLocations, vector<route>& myRoutes, vector<bus>& myBuses){
	int manageLocationsMenuOption;
	do{
		system("cls");
		locate(55, 0); cout << "LOCATION MANAGEMENT\n";
		//menu for what to do with locations
		cout << "\t\t1. Add new Location\n\n";
		cout << "\t\t2. List all Locations\n\n";
		cout << "\t\t3. Search a Location\n\n";
		cout << "\t\t4. Update details of Location\n\n";
		cout << "\t\t5. Remove a Location\n\n";
		cout << "\t\t6. Go back\n\n";
		cout << "\t\tYour choice:"; cin >> manageLocationsMenuOption;
		while (manageLocationsMenuOption <= 0 || manageLocationsMenuOption > 6){
			locate(0, 13); cout << "\t\tYour choice:"; printSpaces(nooOfDigits(manageLocationsMenuOption)); backSpaces(nooOfDigits(manageLocationsMenuOption)); cin >> manageLocationsMenuOption;
		}
		switch (manageLocationsMenuOption){
		case 1:	//Add new location
			AddLocation(myLocations);
			break;
		case 2: //list all Locations
			ListLocations(myLocations);
			break;
		case 3:	//search a location
			SearchLocation(myLocations);
			break;
		case 4:	//Update details of Location
			UpdateLocation(myLocations);
			break;
		case 5:	//Remove a location
			RemoveLocation(myLocations, myRoutes, myBuses);
			break;
		case 7:	//Go back
			break;
		}
	} while (manageLocationsMenuOption != 6);
}
///////////////////////////////////////////////////////////////////////ROUTE MANAGEMENT

void AddRoute(vector<route>& myRoutes, std::vector<location>& myLocations){
	system("cls");
	route tempRoute;
	tempRoute.setDetail(myLocations);
	myRoutes.push_back(tempRoute);
	printSpaces(15); cout << "Route is added...\n";
	printSpaces(15); system("pause");
}

void ListRoutes(vector<route> myRoutes, vector<location> myLocations){
	system("cls");
	locate(55, 0); cout << "LIST ROUTES";
	cout << "\n\n";
	if (myRoutes.size()){
		//Display List of all routes
		for (int i = 0; i < myRoutes.size(); i++){
			myRoutes[i].getDetail(myLocations, i + 1);
		}
	}
	else{
		printSpaces(15); cout<< "No routes added..\n\n\n";
	}
	printSpaces(15); system("pause");
}

vector<route> search(int routeId, vector<route> myRoutes){
	vector<route> temp;
	if (myRoutes.size()){
		for (int i = 0; i < myRoutes.size(); i++){
			if (routeId == myRoutes[i].routeID) temp.push_back(myRoutes[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<route> search(location deptLocataion, vector<route> myRoutes){
	vector<route> temp;
	if (myRoutes.size()){
		for (int i = 0; i < myRoutes.size(); i++){
			if (deptLocataion.locationID == myRoutes[i].departureID) temp.push_back(myRoutes[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<route> search(location destLocation, vector<route> myRoutes, int a){
	vector<route> temp;
	if (myRoutes.size()){
		for (int i = 0; i < myRoutes.size(); i++){
			if (destLocation.locationID == myRoutes[i].destinationID) temp.push_back(myRoutes[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<route> search(route compare_route, vector<route> myRoutes){
	vector<route> temp;
	if (myRoutes.size()){
		for (int i = 0; i < myRoutes.size(); i++){
			if ((compare_route.departureID == myRoutes[i].departureID) && (compare_route.destinationID == myRoutes[i].destinationID)) temp.push_back(myRoutes[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

void SearchRoute(vector<bus> myBuses, vector<route> myRoutes, vector<location> myLocations){
	if (myRoutes.size()){
		//search a route
		int searchRouteMenuOption;
		do{
			system("cls");
			locate(55, 0); cout << "SEARCH ROUTE";
			int RouteID = 0; string DepartureLocation = "", DestinationLocation = ""; vector<route>resultRoutes; bool noneFound = false;
			//menu for how to search route/routes
			locate(15, 3); cout << "1. Search through RouteId\n";
			locate(15, 5); cout << "2. Search through Departure Location\n";
			locate(15, 7); cout << "3. Search through Destination Location\n";
			locate(15, 9); cout << "4. Search through Departure & Destination Location\n";
			locate(15, 11); cout << "5. Exit search page\n";
			locate(15, 13); cout << "Your choice:"; cin >> searchRouteMenuOption;
			while (searchRouteMenuOption <= 0 || searchRouteMenuOption > 5){
				locate(15, 13); cout << "Your choice:"; printSpaces(nooOfDigits(searchRouteMenuOption)); backSpaces(nooOfDigits(searchRouteMenuOption)); cin >> searchRouteMenuOption;
			}
			switch (searchRouteMenuOption){
			case 1:	//RouteID
				printSpaces(15); cout << "Enter RouteID to search: "; cin >> RouteID;
				resultRoutes = search(RouteID, myRoutes);
				if (!resultRoutes.size()) noneFound = true;
				break;
			case 2: //Departure Location
				int whichLocation;
				//display all Locations first
				if (myLocations.size()){
					for (int j = 0; j < myLocations.size(); j++){
						printSpaces(20); cout << j + 1 << ")" << myLocations[j].name << "\n";
					}
					locate(15, 13 + myRoutes.size()); cout << "Select Location:"; cin >> whichLocation;
					while (whichLocation < 1 || whichLocation > myLocations.size()){
						locate(15, 13 + myRoutes.size()); cout << "Select Location:"; printSpaces(nooOfDigits(whichLocation)); backSpaces(nooOfDigits(whichLocation)); cin >> whichLocation;
					}
					resultRoutes = search(myLocations[whichLocation - 1], myRoutes);
					if (!resultRoutes.size())noneFound = true;
				}
				else{
					printSpaces(15); cout << "No location added, so none of the route is set...\n";
					printSpaces(15); noneFound = false;
				}
				break;
			case 3://Destination Location
				int whichDestLocation;
				//display all Locations first
				if (myLocations.size()){
					for (int j = 0; j < myLocations.size(); j++){
						printSpaces(20); cout << j + 1 << ")" << myLocations[j].name << "\n";
					}
					locate(15, 13 + myRoutes.size()); cout << "Select Location:"; cin >> whichDestLocation;
					while (whichDestLocation < 1 || whichDestLocation > myLocations.size()){
						locate(15, 13 + myRoutes.size()); cout << "Select Location:"; printSpaces(nooOfDigits(whichDestLocation)); backSpaces(nooOfDigits(whichDestLocation)); cin >> whichDestLocation;
					}
					resultRoutes = search(myLocations[whichDestLocation - 1], myRoutes, 0);
					if (!resultRoutes.size())noneFound = true;
				}
				else{
					printSpaces(15); cout << "No location added, so none of the route is set...\n";
					noneFound = false;
				}
				break;
			case 4://Departure and Destination Location
				int tempDept, tempDest;
				//display all Locations first
				if (myLocations.size()){
					//first select departure Location
					for (int j = 0; j < myLocations.size(); j++){
						printSpaces(20); cout << j + 1 << ")" << myLocations[j].name << "\n";
					}
					locate(15, 13 + myRoutes.size()); cout << "Select Departure Location:"; cin >> tempDept;
					while (tempDept < 1 || tempDept > myLocations.size()){
						locate(15, 13 + myRoutes.size()); cout << "Select Departure Location:"; printSpaces(nooOfDigits(tempDept)); backSpaces(nooOfDigits(tempDept)); cin >> tempDept;
					}
					//collapse departure location
					locate(15, 14); std::cout << "Departure Location(" << myLocations[tempDept - 1].name << ")";
					for (int i = 13 + myRoutes.size(); i>14; i--){
						locate(0, i); std::cout << "                                                                                          ";
					}
					locate(0, 15);
					//now select destination Location
					for (int j = 0; j < myLocations.size(); j++){
						printSpaces(20); cout << j + 1 << ")" << myLocations[j].name << "\n";
					}
					locate(15, 15+myRoutes.size()); cout << "Select Destination Location:"; cin >> tempDest;
					while (tempDest < 1 || tempDest > myLocations.size()){
						locate(15, 15 + myRoutes.size()); cout << "Select Destination Location:"; printSpaces(nooOfDigits(tempDest)); backSpaces(nooOfDigits(tempDest)); cin >> tempDest;
					}
					//now make temp route and search for result
					route tempRoute;	tempRoute.departureID = myLocations[tempDept - 1].locationID; tempRoute.destinationID = myLocations[tempDest - 1].locationID;
					resultRoutes = search(tempRoute, myRoutes);
					if (!resultRoutes.size())noneFound = true;
				}
				else{
					printSpaces(15); cout << "No location added, so none of the route is set...\n";
					noneFound = false;
				}
				break;
			case 5:	//Exit
				break;
			}
			if (searchRouteMenuOption != 5){
				if (resultRoutes.size())	ListRoutes(resultRoutes, myLocations);
				else{
					printSpaces(15);
					if (noneFound)	cout << "No Route was found with this data...\n";
					printSpaces(15); system("pause");
				}
			}
		} while (searchRouteMenuOption != 5);
	}
	else{
		printSpaces(15); cout << "Nothing to search, no Route added...:'(\n";
		printSpaces(15); system("pause");
	}
}

void UpdateRoute(vector<route>& myRoutes, vector<location>& mylocations){
	int idToUpdate = 0;
	do{
		//find the route and update its data
		if (myRoutes.size()){
			locate(15, 16); cout << "Enter id of the route to update(0 to exit):"; printSpaces(nooOfDigits(idToUpdate)); backSpaces(nooOfDigits(idToUpdate)); cin >> idToUpdate;
			if (idToUpdate){
				for (int i = 0; i < myRoutes.size(); i++){
					if (idToUpdate == myRoutes[i].routeID){
						myRoutes[i].update(mylocations);
						printSpaces(15); cout << "Route's details are updated...\n";
						idToUpdate = 0;
						printSpaces(15); system("pause");
					}
				}
			}
		}
		else{
			printSpaces(15); cout << "Noting to update...no route added...:'(\n";
			printSpaces(15); system("pause");
		}
	} while (idToUpdate != 0);
}

void RemoveRoute(vector<route>& myRoutes, vector<location>& myLocations, vector<bus>& myBuses){
	if (myRoutes.size()){
		int DelRoute;
		locate(15, 16); cout << "Enter Route No to delete:";	cin >> DelRoute;
		while (DelRoute <= 0 || DelRoute > myRoutes.size()){
			locate(15, 16); cout << "Enter Route No to delete:"; printSpaces(nooOfDigits(DelRoute)); backSpaces(nooOfDigits(DelRoute)); cin >> DelRoute;
		}
		//before deleting route, delete its id from locations which are assigned departure or destination
		//First delete route from location which is set as departure location
		for (int i = 0; i < myLocations.size(); i++){
			for (int j = 0; j < myLocations[i].AssignedDeparture.size(); j++){
				if (myRoutes[DelRoute - 1].routeID == myLocations[i].AssignedDeparture[j]){
					//this locations is one set as departure location
					//from its set of AssignedDeparture delete the id of route
					myLocations[i].AssignedDeparture.erase(myLocations[i].AssignedDeparture.begin() + j);
				}
			}
		}
		//Now delete route from location which is set as destination location
		for (int i = 0; i < myLocations.size(); i++){
			for (int j = 0; j < myLocations[i].AssignedDestination.size(); j++){
				if (myRoutes[DelRoute - 1].routeID == myLocations[i].AssignedDestination[j]){
					//this locations is one set as destination location
					//from its set of AssignedDesination delete the id of route
					myLocations[i].AssignedDestination.erase(myLocations[i].AssignedDestination.begin() + j);
				}
			}
		}
		//locations data is updated based on 

		//delete the route from the bus whom it is assigned
		for (int i = 0; i < myRoutes[DelRoute - 1].AssignedToBuses.size(); i++){
			for (int j = 0; j < myBuses.size(); j++){
				if (myBuses[j].BusID == myRoutes[DelRoute - 1].AssignedToBuses[i]){
					//this bus has this route assigned, remove route from it
					myBuses[j].idOfRouteOfBus = -1;
				}
			}
		}
		//now delete the route
		myRoutes.erase(myRoutes.begin() + DelRoute - 1);
		printSpaces(15); cout << "Route is deleted...\n";
	}
	else{
		printSpaces(15); cout << "No routes added..Nothing to delete :'(\n";
	}
	printSpaces(15); system("pause");
}

void manageRoutes(vector<route>& myRoutes, vector<location>& mylocations, vector<bus>& myBuses){

	int manageRouteMenuOption;
	do{
		system("cls");
		locate(55, 0); cout << "MANAGE ROUTES\n";
		//menu for what to do with routes
		cout << "\t\t1. Add new Route\n\n";
		cout << "\t\t2. List all Routes\n\n";
		cout << "\t\t3. Search a Route\n\n";
		cout << "\t\t4. Update details of Route\n\n";
		cout << "\t\t5. Remove a Route\n\n";
		cout << "\t\t6. Manage Locations\n\n";
		cout << "\t\t7. Go back\n\n";
		cout << "\t\tYour choice:"; cin >> manageRouteMenuOption;
		while (manageRouteMenuOption <= 0 || manageRouteMenuOption > 7){
			locate(0, 15); cout << "\t\tYour choice:"; printSpaces(nooOfDigits(manageRouteMenuOption)); backSpaces(nooOfDigits(manageRouteMenuOption)); cin >> manageRouteMenuOption;
		}
		switch (manageRouteMenuOption){
		case 1:	//Add new route
			AddRoute(myRoutes, mylocations);
			break;
		case 2: //list all Routes
			ListRoutes(myRoutes, mylocations);
			break;
		case 3:	//search a route
			SearchRoute(myBuses, myRoutes, mylocations);
			break;
		case 4:	//Update details of route
			UpdateRoute(myRoutes, mylocations);
			break;
		case 5:	//Remove a route
			RemoveRoute(myRoutes, mylocations, myBuses);
			break;
		case 6:	//Manage locations
			managelocations(mylocations, myRoutes, myBuses);
			break;
		case 7:	//Go back
			break;
		}
	} while (manageRouteMenuOption != 7);
}


///////////////////////////////////////////////////////////////////////DRIVER MANAGEMENT

//functions for features of manage drivers
void hireDriver(vector<driver>& myDrivers){
	system("cls");
	locate(55, 0); std::cout << "HIRE DRIVER";
	//hire new driver
	driver tempDriver;
	tempDriver.setDriverDetails(15,2);
	myDrivers.push_back(tempDriver);
	//driver is added in staff
	printSpaces(15); std::cout << "Driver is hired...\n"; printSpaces(15);
	system("pause");
}

void listDrivers(vector<driver> myDrivers){
	int selectedDriver;
	do{
		system("cls");
		cout << "\n\n";
		if (myDrivers.size()){
			//Display List of all drivers
			for (int i = 0; i < myDrivers.size(); i++){
				printSpaces(15);
				myDrivers[i].getDriverDetails(i + 1);
			}
			locate(15, 6 + myDrivers.size()); cout << "Select Driver to view his/her details(0 to exit):"; cin >> selectedDriver;
			while (selectedDriver<0 || selectedDriver>myDrivers.size()){
				locate(15, 6 + myDrivers.size());	cout << "Select Driver to view his/her details(0 to exit):"; printSpaces(nooOfDigits(selectedDriver)); backSpaces(nooOfDigits(selectedDriver)); cin >> selectedDriver;
			}
			//goto bus's detailed page
			if (selectedDriver != 0) myDrivers[selectedDriver - 1].detailedPage();
		}
		else{
			printSpaces(15); cout << "NO DRIVERS HIRED!!!\n\n";
			printSpaces(15); system("pause");
			selectedDriver = 0;
		}
	} while (selectedDriver != 0);

}

vector<driver> search(int driverID, vector<driver> myDrivers){
	vector<driver> temp;
	if (myDrivers.size()){
		for (int i = 0; i < myDrivers.size(); i++){
			if (driverID == myDrivers[i].DriversID) temp.push_back(myDrivers[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<driver> search(string driverName, vector<driver> myDrivers){
	vector<driver> temp;
	if (myDrivers.size()){
		for (int i = 0; i < myDrivers.size(); i++){
			if (driverName == myDrivers[i].name) temp.push_back(myDrivers[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

vector<driver> search(int CNIC, vector<driver> myDrivers, int a){
	vector<driver> temp;
	if (myDrivers.size()){
		for (int i = 0; i < myDrivers.size(); i++){
			if (CNIC == myDrivers[i].CNIC) temp.push_back(myDrivers[i]);
		}
		return temp;
	}
	else{
		return temp;
	}
}

void searchDriver(vector<driver> myDrivers){
	if (myDrivers.size()){
		//search a location
		int searchDriverMenuOption;
		do{
			system("cls");
			locate(55, 0); cout << "SEARCH DRIVER";
			int DriverID = 0; long long CNIC; string DriverName = ""; vector<driver>resultDrivers; bool noneFound = false;
			//menu for how to search Driver/Drivers
			locate(15, 3); cout << "1. Search through DriverId\n";
			locate(15, 5); cout << "2. Search through DriverName\n";
			locate(15, 7); cout << "3. Search through CNIC\n";
			locate(15, 9); cout << "4. Exit search page\n";
			locate(15, 11); cout << "Your choice:"; cin >> searchDriverMenuOption;
			while (searchDriverMenuOption <= 0 || searchDriverMenuOption > 4){
				locate(15, 11); cout << "Your choice:"; printSpaces(nooOfDigits(searchDriverMenuOption)); backSpaces(nooOfDigits(searchDriverMenuOption)); cin >> searchDriverMenuOption;
			}
			switch (searchDriverMenuOption){
			case 1:	//DriverID
				printSpaces(15); cout << "Enter DriverID to search: "; cin >> DriverID;
				resultDrivers = search(DriverID, myDrivers);
				if (!resultDrivers.size()) noneFound = true;
				break;
			case 2: //DriverName
				printSpaces(15); cout << "Enter DriverName to search: "; cin >> DriverName;
				resultDrivers = search(DriverName, myDrivers);
				if (!resultDrivers.size())noneFound = true;
				break;
			case 3://CNIC
				printSpaces(15); cout << "Enter CNIC to search: "; cin >> CNIC;
				resultDrivers = search(CNIC, myDrivers, 0);
				if (!resultDrivers.size())noneFound = true;
				break;
			case 4:	//Exit
				break;
			}
			if (searchDriverMenuOption != 4){
				if (resultDrivers.size())	listDrivers(resultDrivers);
				else{
					if (noneFound){ printSpaces(15); cout << "No Driver was found with this data...\n"; }
					printSpaces(15); system("pause");
				}
			}
		} while (searchDriverMenuOption != 4);
	}
	else{
		printSpaces(15); cout << "Nothing to search, no Drivers added...:'(\n";
		printSpaces(15); system("pause");
	}
}

void updateDriver(vector<driver>& myDrivers){
	//find the driver and update his/her data
	int idToUpdate = 0;
	do{
		//find the location and update its data
		if (myDrivers.size()){
			locate(15, 16); cout << "Enter id of the Driver to update(0 to exit):"; printSpaces(nooOfDigits(idToUpdate)); backSpaces(nooOfDigits(idToUpdate)); cin >> idToUpdate;
			if (idToUpdate){
				for (int i = 0; i < myDrivers.size(); i++){
					if (idToUpdate == myDrivers[i].DriversID){
						myDrivers[i].update();
						printSpaces(15); cout << "Driver's detail is updated...\n";
						idToUpdate = 0;
						printSpaces(15); system("pause");
					}
				}
			}
		}
		else{
			printSpaces(15); cout << "Noting to update...no Driver hired...:'(\n";
			printSpaces(15); system("pause");
		}
	} while (idToUpdate != 0);
}

void fireDriver(vector<driver>& myDrivers, vector<bus>& mybuses){
	int id;
	if (myDrivers.size()){
		locate(15, 14); cout << "Fire driver with id:"; cin >> id;
		while (id <= 0 || id > myDrivers[myDrivers.size() - 1].DriversID){
			locate(15, 14); cout << "Fire driver with id:"; printSpaces(nooOfDigits(id)); backSpaces(nooOfDigits(id)); cin >> id;
		}
		//before firing driver delete his id from buses he is assigned to:
		for (int i = 0; i < myDrivers[id - 1].AssignedBuses.size(); i++){
			//find the bus with id
			for (int j = 0; j < mybuses.size(); j++){
				if (mybuses[j].BusID == myDrivers[id - 1].AssignedBuses[i]){
					//this is the bus the driver is assigned to, remove his id
					mybuses[j].idOfDriverOfBus = -1;
				}
			}
		}

		myDrivers.erase(myDrivers.begin() + id - 1);
		printSpaces(15); cout << "Driver fired...\n";
	}
	else{
		printSpaces(15); cout << "No driver to fire :'(\n";
	}
	printSpaces(15); system("pause");
}

void manageDrivers(vector<driver>& myDrivers, vector<bus>& myBuses){
	int manageDriverMenuOption;
	do{
		system("cls");
		locate(55, 0); cout << "DRIVER MANAGEMENT\n";
		//menu for what to do with drivers
		cout << "\t\t1. Hire new Driver\n\n";
		cout << "\t\t2. List all Drivers\n\n";
		cout << "\t\t3. Search a Driver\n\n";
		cout << "\t\t4. Update details of Driver\n\n";
		cout << "\t\t5. Fire a Driver\n\n";
		cout << "\t\t6. Go back\n\n";
		cout << "\t\tYour choice:"; cin >> manageDriverMenuOption;
		while (manageDriverMenuOption <= 0 || manageDriverMenuOption > 6){
			locate(0, 13); cout << "\t\tYour choice::"; printSpaces(nooOfDigits(manageDriverMenuOption)); backSpaces(nooOfDigits(manageDriverMenuOption)); cin >> manageDriverMenuOption;
		}
		switch (manageDriverMenuOption){
		case 1:	//Hire new Driver
			hireDriver(myDrivers);
			break;
		case 2: //list all Drivers
			listDrivers(myDrivers);
			break;
		case 3:	//search a Driver
			searchDriver(myDrivers);
			break;
		case 4:	//Update details of driver
			updateDriver(myDrivers);
			break;
		case 5:	//Fire a driver
			fireDriver(myDrivers, myBuses);
			break;
		case 6:	//Go back
			break;
		}
	} while (manageDriverMenuOption != 6);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////ADMIN CONTROLS END HERE/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void generalMenu(){
	system("cls");
	locate(55, 0); cout << "GENERAL ACCOUNT\n";
	cout << "\t\t1. Book a seat\n\n";
	cout << "\t\t2. See booking details\n\n";
	cout << "\t\t3. Cancel your booking\n\n";
	cout << "\t\t4. Exit\n\n";
}

int temp2Original_bus(vector<bus> MyBuses, int ID){
	for (int i = 0; i < MyBuses.size(); i++){
		if (MyBuses[i].BusID == ID) return i;
	}
	return -1;
}

void bookSeat(vector<bus>& myBuses, vector<route>myRoutes, vector<location>myLocations, vector<ticket>& myTickets){
	//copy all valid buses to tempBuses
	vector<bus> tempBuses;;
	for (int i = 0; i < myBuses.size(); i++){
		if (myBuses[i].isAvailabe()) tempBuses.push_back(myBuses[i]);
	}
	int bookingOption, bookBusNo, bookBusIndex;

	int filterChoice = 3;
	if (tempBuses.size()){
		do{
			int line = 3, filterType;
			system("cls");
			//display buses from tempBuses
			locate(0, 1); cout << "S.No";
			locate(5, 1); cout << "Bus Name";		locate(15, 1); cout << "Departure Location";		locate(40, 1); cout << "Destination Location";
			locate(65, 1); cout << "No Of Seats";		locate(85, 1); cout << "Date";		locate(100, 1); cout << "Time";		locate(110, 1); cout << "Price\n";

			for (int i = 0; i < tempBuses.size(); i++){
				locate(0, line); cout << i + 1 << ")";
				tempBuses[i].displayForBooking(myLocations, myRoutes, line++);
			}//what if temp size becomes zero after filter, such that no result for that data was found

			cout << "\nFilter?(1/0)"; cin >> filterChoice;
			while (filterChoice != 0 && filterChoice != 1){
				cout << "Wrong choice..Enter again(1/0):"; cin >> filterChoice;
			}
			if (filterChoice == 1){
				//filter
				cout << "Filter by:\n1)Departure Location\n2)Destination Location\nYour Choice:"; cin >> filterType;
				while (filterType<1 && filterType >2){
					cout << "Wrong choice..Enter again:"; cin >> filterType;
				}

				int whichLocation, departureListLine = 1;
				vector<route>resultRoutes;	vector<location> tempLocations;	vector<bus>resultBuses;
				switch (filterType){
				case 1://departure location
					int filterDept;
					//FIRST FIND VALID DEPARTURE LOCATOINS: copy valid dept locations int temp variable
					for (int i = 0; i < tempBuses.size(); i++){//loop through all temp buses and find their route
						for (int r = 0; r < myRoutes.size(); r++){//loop through all routes find the route of the bus
							if (tempBuses[i].idOfRouteOfBus == myRoutes[r].routeID){//if route is found
								for (int l = 0; l < myLocations.size(); l++){//loop through all location and find departure location of this route
									if (myLocations[l].locationID == myRoutes[r].departureID){//if id of location matches with departure id
										bool isAlreadyAdded = false;
										//if it is not already added then add it in tempLocations
										for (int k = 0; k < tempLocations.size(); k++){
											if (myLocations[l].locationID == tempLocations[k].locationID) isAlreadyAdded = true;
										}
										if (!isAlreadyAdded)	tempLocations.push_back(myLocations[l]);//then add that location in tempLocations
									}
								}
							}
						}
					}
					//NOW FIND DISPLAY VALID DEPARTURE LOCATOIN: print all valid departure locations(temp locations)
					for (int i = 0; i < tempLocations.size(); i++){
						cout << i + 1 << ")" << tempLocations[i].name << "\n";
					}
					if (tempLocations.size()){
						cout << "Your choice:"; cin >> filterDept;
						while (filterDept<1 || filterDept>tempLocations.size()){
							cout << "Wong choice...Select Again:"; cin >> filterDept;
						}

						//filter tempBuses by seleted Departure Location
						resultRoutes = search(tempLocations[filterDept - 1], myRoutes);
						//free tempBuses
						vector<bus>temp = tempBuses;
						tempBuses.erase(tempBuses.begin(), tempBuses.end());
						//now update tempBuses with filtered result
						for (int i = 0; i < resultRoutes.size(); i++){
							resultBuses = search(resultRoutes[i], temp);
							for (int j = 0; j < resultBuses.size(); j++){
								tempBuses.push_back(resultBuses[j]);
							}
						}
					}
					else{
						//no departure location set....This condition is unneccsessary now because only valid buses are shown so there must be valid dept location
						cout << "Sorry cant filter by departure location...\n";
					}
					break;
				case 2://destination location
					int filterDest;
					//FIRST FIND VALID DESTINATION LOCATOINS: copy valid dest locations int temp variable
					for (int i = 0; i < tempBuses.size(); i++){//loop through all temp buses and find their route
						for (int r = 0; r < myRoutes.size(); r++){//loop through all routes find the route of the bus
							if (tempBuses[i].idOfRouteOfBus == myRoutes[r].routeID){//if route is found
								for (int l = 0; l < myLocations.size(); l++){//loop through all location and find destination location of this route
									if (myLocations[l].locationID == myRoutes[r].destinationID){//if id of location matches with destination id
										bool isAlreadyAdded = false;
										//if it is not already added then add it in tempLocations
										for (int k = 0; k < tempLocations.size(); k++){
											if (myLocations[l].locationID == tempLocations[k].locationID) isAlreadyAdded = true;
										}
										if (!isAlreadyAdded)	tempLocations.push_back(myLocations[l]);//then add that location in tempLocations
									}
								}
							}
						}
					}
					//NOW FIND DISPLAY VALID DESTINATION LOCATOIN: print all valid destination locations(temp locations)
					for (int i = 0; i < tempLocations.size(); i++){
						cout << i + 1 << ")" << tempLocations[i].name << "\n";
					}
					if (tempLocations.size()){
						cout << "Your choice:"; cin >> filterDest;
						while (filterDest<1 || filterDest>tempLocations.size()){
							cout << "Wong choice...Select Again:"; cin >> filterDest;
						}

						//filter tempBuses by seleted Departure Location
						resultRoutes = search(tempLocations[filterDest - 1], myRoutes, 1);
						//free tempBuses
						vector<bus>temp = tempBuses;
						tempBuses.erase(tempBuses.begin(), tempBuses.end());
						//now update tempBuses with filtered result
						for (int i = 0; i < resultRoutes.size(); i++){
							resultBuses = search(resultRoutes[i], temp);
							for (int j = 0; j < resultBuses.size(); j++){
								tempBuses.push_back(resultBuses[j]);
							}
						}

					}
					else{
						//no destination location set....This condition is unneccsessary now because only valid buses are shown so there must be valid dest location
						cout << "Sorry cant filter by destination location...\n";
					}
					break;
				}
			}
		} while (filterChoice != 0);//filter ended

		cout << "Book?(1/0)"; cin >> bookingOption;
		while (bookingOption != 1 && bookingOption != 0){
			cout << "Wrong option...Enter again:"; cin >> bookingOption;
		}
		if (bookingOption){
			vector <int> bookedSeats;
			cout << "Select Bus:"; cin >> bookBusNo;
			while (bookBusNo<1 || bookBusNo>tempBuses.size()){
				cout << "Wrong option...Select again:"; cin >> bookBusNo;
			}
			bookBusIndex = temp2Original_bus(myBuses, tempBuses[bookBusNo - 1].BusID);
			//do the booking
			bookedSeats = myBuses[bookBusIndex].booking();
			//generate the ticket
			ticket t;
			t.enterData(myBuses[bookBusIndex].BusID, bookedSeats);
			//add the ticket in ticket collection
			myTickets.push_back(t);
			//print the ticket
			t.printTicket(myBuses, myLocations, myRoutes);
		}
	}
	else{
		cout << "Sorry!, currently we donot have any bus :(...\n";
	}
	system("pause");
}

int search(vector<ticket> myTickets, int ID){
	for (int i = 0; i < myTickets.size(); i++){
		if (myTickets[i].ticketID == ID) return i;
	}
	return -1;
}

void seeBookingDetails(vector<bus> buses, vector<route> routes, vector<location> Locations, vector<ticket> myTickets){
	if (myTickets.size()){
		int ID, index;
		cout << "\t\tEnter ticket ID to view:"; cin >> ID;
		index = search(myTickets, ID);
		if (index != -1){
			if (search(myTickets[index].busID, buses).size()){
				myTickets[index].printTicket(buses, Locations, routes);
			}
			else{
				cout << "\n\t\tSorry due to unavabilty of certain bus, your booking is canceled...\n\t\t";
			}
		}
		else{
			cout << "\t\tTicket with this ID not found.\n\t\t";
		}
	}
	else{
		cout << "\t\tNo recods added(no seat booked)...nothing to search\n\t\t";
	}
	system("pause");
}

void removeBooking(vector<bus>& buses, vector<route> routes, vector<location> Locations, vector<ticket>& myTickets){
	if (myTickets.size()){
		//delete the booking data from seat
		//delete the ticket from collection
		int ID, index, cancel;
		cout << "\t\tEnter ticket ID to cancel booking:"; cin >> ID;
		index = search(myTickets, ID);
		if (index != -1){
			if (search(myTickets[index].busID, buses).size()){
				myTickets[index].printTicket(buses, Locations, routes);
				cout << "\n\t\tThis order will be canceled..Cancel(1/0):"; cin >> cancel;
				while (cancel != 1 && cancel != 0){
					cout << "wrong option...enter again:"; cin >> cancel;
				}
				if (cancel){
					//find the bus
					for (int i = 0; i < buses.size(); i++){
						if (buses[i].BusID == myTickets[index].busID){
							//unbook all seats booked from the book
							for (int j = 0; j < myTickets[index].seatNos.size(); j++){
								buses[i].Seats[myTickets[index].seatNos[j] - 1].unBook();
							}
						}
					}
					//delete the ticket
					myTickets.erase(myTickets.begin() + index);
				}
			}
			else{
				cout << "\n\t\tSorry due to unavabilty of certain bus, your booking already is canceled...\n\t\t";
			}
		}
		else{
			cout << "\t\tTicket with this ID not found.\n\t\t";
		}
	}
	else{
		cout << "\t\tNo records added(no seat is booked)....\n\t\t";
	}
	system("pause");
}