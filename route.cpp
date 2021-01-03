#include"route.h"

//initialize static ints
int route::nextID = 0;
int location::nextID = 0;


void location::setLocation(){
	std::cout << "\t\tEnter name of location:"; std::cin >> name;
	std::cout << "\t\tSet x-cod for the location:"; std::cin >> x_cod;
	std::cout << "\t\tSet y-cod for the location:"; std::cin >> y_cod;
}

void route::setDetail(std::vector<location>& myLocations){
	system("cls");
	locate(55, 0); std::cout << "ADD ROUTE\n\n";
	bool isDeptSet = false;
	int deptchoice = 0;
	do{
		locate(15, 2); std::cout << "Deparure location:\n";
		printSpaces(15); std::cout << "1)Add from my locations list\n";
		printSpaces(15); std::cout << "2)Add new location and set it departure location of this route\n";
		printSpaces(15); std::cout << "Your choice :"; printSpaces(nooOfDigits(deptchoice)); backSpaces(nooOfDigits(deptchoice)); std::cin >> deptchoice;
		while (deptchoice != 1 && deptchoice != 2){
			locate(15, 5); std::cout << "Your choice :"; printSpaces(nooOfDigits(deptchoice)); backSpaces(nooOfDigits(deptchoice)); std::cin >> deptchoice;
		}
		if (deptchoice == 1){
			int whichLocation;
			//from my collection
			if (myLocations.size()){
				for (int i = 0; i < myLocations.size(); i++){
					printSpaces(20); std::cout << i + 1 << ")" << myLocations[i].name << "\n";
				}
				locate(15, 6 + myLocations.size()); std::cout << "Select:"; std::cin >> whichLocation;
				while (whichLocation<0 || whichLocation>myLocations.size()){
					locate(15, 6 + myLocations.size()); std::cout << "Select:"; printSpaces(nooOfDigits(whichLocation)); backSpaces(nooOfDigits(whichLocation)); std::cin >> whichLocation;
				}
				departureID = myLocations[whichLocation - 1].locationID;//Location is set:. its id is saved
				myLocations[whichLocation - 1].AssignedDeparture.push_back(routeID);
				//collapse departure location
				locate(33, 2); std::cout << "(" << myLocations[whichLocation - 1].name << ")          ";
				for (int i = 7 + myLocations.size(); i>2; i--){
					locate(0, i); std::cout << "                                                                                                    ";
				}
				isDeptSet = true;
			}
			else{
				locate(33, 2); std::cout << "(None added)";
			}
		}
		else{
			//create new location
			location tempLocation;
			tempLocation.setLocation();
			departureID = tempLocation.locationID;//Location is set:. its id is saved
			tempLocation.AssignedDeparture.push_back(routeID);

			myLocations.push_back(tempLocation);
			//collapse departure location
			locate(33, 2); std::cout << "(" << tempLocation.name << ")          ";
			for (int i = 9; i > 2; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
			isDeptSet = true;
		}
	} while (!isDeptSet);
	//Departure location is set up now

	bool isDestSet = false;
	int destchoice;
	do{
		locate(15, 3); std::cout << "Destination location:";
		locate(15, 4); std::cout << "1)Add from my locations list";
		locate(15, 5); std::cout << "2)Add new location and set it departure location of this route";
		locate(15, 6); std::cout << "Your choice:"; std::cin >> destchoice;
		while (destchoice != 1 && destchoice != 2){
			locate(15, 6); std::cout << "Your choice:"; printSpaces(nooOfDigits(destchoice)); backSpaces(nooOfDigits(destchoice)); std::cin >> destchoice;
		}
		if (destchoice == 1){
			int whichLocation;
			//from my collection
			if (myLocations.size()){
				for (int i = 0; i < myLocations.size(); i++){
					printSpaces(20); std::cout << i + 1 << ")" << myLocations[i].name << "\n";
				}
				locate(15, 7 + myLocations.size()); std::cout << "Select:"; std::cin >> whichLocation;
				while (whichLocation<1 || whichLocation>myLocations.size()){
					locate(15, 7 + myLocations.size()); std::cout << "Select:"; printSpaces(nooOfDigits(whichLocation)); backSpaces(nooOfDigits(whichLocation)); std::cin >> whichLocation;
				}
				destinationID = myLocations[whichLocation - 1].locationID;//Location is set:. its id is saved
				myLocations[whichLocation - 1].AssignedDestination.push_back(routeID);
				//collapse destination location
				locate(36, 3); std::cout << "(" << myLocations[whichLocation - 1].name << ")      ";
				for (int i = 7 + myLocations.size(); i > 3; i--){
					locate(0, i); std::cout << "                                                                                                    ";
				}
				isDestSet = true;
			}
			else{
				locate(36, 3); std::cout << "(None added)";
			}
		}
		else{
			//create new location
			location tempLocation;
			tempLocation.setLocation();
			destinationID = tempLocation.locationID;//Location is set:. its id is saved
			tempLocation.AssignedDestination.push_back(routeID);

			myLocations.push_back(tempLocation);
			//collapse destination location
			locate(36, 3); std::cout << "(" << tempLocation.name << ")      ";
			for (int i = 9; i > 3; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
			isDestSet = true;
		}
	} while (!isDestSet);
	//Destination location is set up now
	locate(15, 4); std::cout << "Set rate per Km for this route:"; std::cin >> ratePERkm;

	updateDistanceFare(myLocations);
}

void route::updateDistanceFare(std::vector<location>& myLocations){
	if (departureID != -1 && destinationID != -1){
		//update value of distance and fare
		location tempDept, tempDest;
		for (int i = 0; i < myLocations.size(); i++){
			if (departureID == myLocations[i].locationID){
				tempDept = myLocations[i];
			}
		}
		for (int i = 0; i < myLocations.size(); i++){
			if (destinationID == myLocations[i].locationID){
				tempDest = myLocations[i];
			}
		}
		distance = (tempDept.x_cod - tempDest.x_cod) + (tempDept.y_cod - tempDest.y_cod);
		if (distance < 0) distance *= -1;
		fare = ratePERkm*distance;
	}
	else{
		distance = -1;
		fare = -1;
	}
}

void route::getDetail(std::vector<location> myLocations,int i){
	printSpaces(15); std::cout << i << ")\n";
	printSpaces(15); std::cout << "RouteID:" << routeID << "\n";
	if (departureID != -1){
		for (int i = 0; i < myLocations.size(); i++){
			if (departureID == myLocations[i].locationID){
				printSpaces(15); std::cout << "Departure location:" << myLocations[i].name << "\n";
			}
		}
	}
	else{
		printSpaces(15); std::cout << "Departure location: Not set yet\n";
	}
	if (destinationID != -1){
		for (int i = 0; i < myLocations.size(); i++){
			if (destinationID == myLocations[i].locationID){
				printSpaces(15); std::cout << "Destination location:" << myLocations[i].name << "\n";
			}
		}
	}
	else{
		printSpaces(15); std::cout << "Destination location: Not set yet\n";
	}
	printSpaces(15);
	if (distance != -1)	std::cout << "Distance:" << distance << "\n";
	else 	std::cout << "Distance: N/A\n";

	printSpaces(15);
	if (fare != -1)		std::cout << "Fare:" << fare << "\n";
	else 	std::cout << "Fare: N/A\n";
	//print all buses this route is assigned to
	for (int i = 0; i < AssignedToBuses.size(); i++){
		printSpaces(20); std::cout << "Assigned to bus:" << AssignedToBuses[i] << "\n";
	}
	std::cout << "\n\n";
}

void route::update(std::vector<location>& myLocations){
	system("cls");
	locate(55, 0); std::cout << "UPDATE ROUE";
	//dept and dest location, rate per km
	int tempRPKM;
	std::string updateDept, updateDest;
	locate(15, 3); std::cout << "Update Departure Location:(y/n)"; std::cin >> updateDept;
	while (updateDept != "n" && updateDept != "N" && updateDept != "y" && updateDept != "Y"){
		locate(15, 3); std::cout << "Update Departure Location:(y/n)"; std::cin >> updateDept;
	}
	if (updateDept != "n" && updateDept != "N"){
		//first delete this route from previous assigned departure location's assigned as dept location list if route has any prev departure location
		if (departureID != -1){
			for (int i = 0; i < myLocations.size(); i++){
				if (departureID == myLocations[i].locationID){
					for (int j = 0; j < myLocations[i].AssignedDeparture.size(); j++){
						if (myLocations[i].AssignedDeparture[j] == routeID){
							myLocations[i].AssignedDeparture.erase(myLocations[i].AssignedDeparture.begin() + j);
						}
					}
				}
			}
		}
		int whichDept, method;
		//select new or create new
		locate(15, 4); std::cout << "1:Select from existing locations list\n";
		locate(15, 5); std::cout << "2:Add new location and set it departure location of this route\n";
		locate(15, 6); std::cout << "Your choice:"; std::cin >> method;
		while (method<1 || method>2){
			locate(15, 6); std::cout << "Your choice:"; printSpaces(nooOfDigits(method)); backSpaces(nooOfDigits(method)); std::cin >> method;
		}
		if (method == 1){
			//select from exiting locations
			//display all locations to update departure location
			for (int i = 0; i < myLocations.size(); i++){
				printSpaces(20); std::cout << i + 1 << ")" << myLocations[i].name << "\n";
			}
			locate(15, 6 + myLocations.size()); std::cout << "Your choice:"; std::cin >> whichDept;
			while (whichDept<1 || whichDept>myLocations.size()){
				locate(15, 6 + myLocations.size()); std::cout << "Your choice:"; printSpaces(nooOfDigits(whichDept)); backSpaces(nooOfDigits(whichDept)); std::cin >> whichDept;
			}
			departureID = myLocations[whichDept - 1].locationID;
			//now go in locations assigned dest location list and add this route in it
			myLocations[whichDept - 1].AssignedDeparture.push_back(routeID);
			//collapse departure location
			locate(47, 3); std::cout << "(" << myLocations[whichDept - 1].name << ")";
			for (int i = 8 + myLocations.size(); i > 3; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
		}
		else{
			//create new and assign it to this route
			location tempDeptLocation;
			tempDeptLocation.setLocation();
			departureID = tempDeptLocation.locationID;//Location is set:. its id is saved
			tempDeptLocation.AssignedDeparture.push_back(routeID);

			myLocations.push_back(tempDeptLocation);
			//collapse departure location
			locate(47, 3); std::cout << "(" << tempDeptLocation.name << ")";
			for (int i = 15; i > 3; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
		}
	}//dept location is dealt

	locate(15, 4); std::cout << "Update Destination Location:(y/n)"; std::cin >> updateDest;
	while (updateDest != "n" && updateDest != "N" && updateDest != "y" && updateDest != "Y"){
		locate(15, 4); std::cout << "Update Destination Location:(y/n)"; std::cin >> updateDest;
	}
	if (updateDest != "n" && updateDest != "N"){
		//first delete this route from previous assigned destination location's assigned as dest location list if route has any prev dest location
		if (destinationID != -1){
			for (int i = 0; i < myLocations.size(); i++){
				if (destinationID == myLocations[i].locationID){
					for (int j = 0; j < myLocations[i].AssignedDestination.size(); j++){
						if (myLocations[i].AssignedDestination[j] == routeID){
							myLocations[i].AssignedDestination.erase(myLocations[i].AssignedDestination.begin() + j);
						}
					}
				}
			}
		}
		int whichDest, methodDest;
		//select new or create new
		locate(15, 5); std::cout << "1:Select from existing locations list\n";
		locate(15, 6); std::cout << "2:Add new location and set it destination location of this route\n";
		locate(15, 7); std::cout << "Your choice:"; std::cin >> methodDest;
		while (methodDest<1 || methodDest>2){
			locate(15, 7); std::cout << "Your choice:"; printSpaces(nooOfDigits(methodDest)); backSpaces(nooOfDigits(methodDest)); std::cin >> methodDest;
		}
		if (methodDest == 1){
			//select from exiting locations
			//display all locations to update destination location
			for (int i = 0; i < myLocations.size(); i++){
				printSpaces(20); std::cout << i + 1 << ")" << myLocations[i].name << "\n";
			}
			locate(15, 8 + myLocations.size()); std::cout << "Your choice:"; std::cin >> whichDest;
			while (whichDest<1 || whichDest>myLocations.size()){
				locate(15, 8 + myLocations.size()); std::cout << "Your choice:"; printSpaces(nooOfDigits(whichDest)); backSpaces(nooOfDigits(whichDest)); std::cin >> whichDest;
			}
			destinationID = myLocations[whichDest - 1].locationID;
			//now go in locations assigned dest location list and add this route in it
			myLocations[whichDest - 1].AssignedDestination.push_back(routeID);
			//collapse destination location
			locate(49, 4); std::cout << "(" << myLocations[whichDest - 1].name << ")";
			for (int i = 9 + myLocations.size(); i > 4; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
		}
		else{
			//create new and assign it to this route
			location tempDestLocation;
			tempDestLocation.setLocation();
			destinationID = tempDestLocation.locationID;//Location is set:. its id is saved
			tempDestLocation.AssignedDestination.push_back(routeID);

			myLocations.push_back(tempDestLocation);
			//collapse destination location
			locate(49, 4); std::cout << "(" << tempDestLocation.name << ")";
			for (int i = 16; i > 4; i--){
				locate(0, i); std::cout << "                                                                                                    ";
			}
		}
	}//dest location is dealt
	locate(15, 5); std::cout << "Update rate per km:(-1 to donot change)"; std::cin >> tempRPKM;
	if (tempRPKM != -1)	ratePERkm = tempRPKM;
	updateDistanceFare(myLocations);
}

void location::getDetails(int i){
	printSpaces(15); std::cout << i << ")\n";
	printSpaces(15); std::cout << "LocationID:" << locationID << "\n";
	printSpaces(15); std::cout << "Name:" << name << "\n";
	printSpaces(15); std::cout << "X-Cod:" << x_cod << "\n";
	printSpaces(15); std::cout << "Y-Cod:" << y_cod << "\n";
	//print all routes's id whose departure location is this location
	for (int i = 0; i < AssignedDeparture.size(); i++){
		printSpaces(20); std::cout << "This location is set departure location for route" << AssignedDeparture[i] << "\n";
	}
	//print all routes's id whose destination location is this location
	for (int i = 0; i < AssignedDestination.size(); i++){
		printSpaces(20); std::cout << "This location is set destination location for route" << AssignedDestination[i] << "\n";
	}
}

void location::update(){
	std::string tempName; int tempX, tempY;
	printSpaces(15); std::cout << "Enter new data to Update and -1 to not change prev data:\n";
	printSpaces(15); std::cout << "Update name:"; std::cin >> tempName;
	if (tempName != "-1") name = tempName;
	printSpaces(15); std::cout << "Update X-Cod:"; std::cin >> tempX;
	if (tempX != -1) x_cod = tempX;
	printSpaces(15); std::cout << "Update Y-Cod:"; std::cin >> tempY;
	if (tempY != -1) y_cod = tempY;
}