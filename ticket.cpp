#include"ticket.h"

int ticket::nextID = 0;

void ticket::enterData(int bus, std::vector<int> seats){
	busID = bus;
	seatNos = seats;
}

int search(std::vector<bus>myBuses, int ID){
	for (int i = 0; i < myBuses.size(); i++){
		if (myBuses[i].BusID == ID) return i;
	}
	return -1;
}

int search(std::vector<route> myRoutes, int ID){
	for (int i = 0; i < myRoutes.size(); i++){
		if (myRoutes[i].routeID == ID) return myRoutes[i].departureID;
	}
	return -1;
}

int search(std::vector<route> myRoutes, int ID, int a){
	for (int i = 0; i < myRoutes.size(); i++){
		if (myRoutes[i].routeID == ID) return myRoutes[i].destinationID;
	}
	return -1;
}

void ticket::printTicket(std::vector<bus>myBuses, std::vector<location>myLocations, std::vector<route> myRoutes){
	bus tempBus = myBuses[search(myBuses, busID)];
	system("cls");
	std::cout << "TICKET ID: " << ticketID << "\n";
	for (int i = 0; i < seatNos.size(); i++){
		int tempSeatNo = seatNos[i];
		seat tempSeat = tempBus.Seats[tempSeatNo - 1];
		std::cout << "SEAT NO: " << tempSeatNo; if (tempSeat.isBusiness){ std::cout << "(Business)"; }
		else{ std::cout << "(Economy)"; }
		std::cout << "\nCUSTOMER DETAILS:\n";
		tempSeat.customer.printPerson(10);
	}
	std::cout << "BOOKING DETAILS:\n";
	std::cout << "BUS NAME:" << tempBus.busName << "\n";
	std::cout << "DEPARTURE LOCATION: " << myLocations[tempBus.getLocation(myLocations, search(myRoutes, tempBus.idOfRouteOfBus))].name << "\n";
	std::cout << "DESTINATION LOCATION: " << myLocations[tempBus.getLocation(myLocations, search(myRoutes, tempBus.idOfRouteOfBus, 0))].name << "\n";
	std::cout << "DEPARTURE DATE: " << tempBus.DepartureDate << "\n";
	std::cout << "DEPARTURE TIME: " << tempBus.DepartureTime << "\n";
	std::cout << "Total fare:" << tempBus.fare*seatNos.size() << "\n";
	std::cout << "THANK YOU FOR CHOOSING OUR SERVICE!, HOPE YOU ENJOY THE RIDE\n";

}