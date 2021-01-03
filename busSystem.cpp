#include"functions.h"
using namespace std;

int main(){
	vector<bus>Buses;	vector<driver>Drivers;	vector<route> Routes;	vector<location> locations;	vector<ticket> Tickets;
	int option;
	//Load starter data
	loadStarterData(Buses, Drivers, Routes, locations);
	
	do{
		system("cls");
		option = chooseAccountType();
		if (option == 1){
			//admin
			int adminMenuChoice;
			do{
				system("cls");
				locate(55, 0); cout << "Welcome ADMIN\n";
				adminMenu();
				printSpaces(10); cout << "Choice:"; cin >> adminMenuChoice;
				switch (adminMenuChoice){
				case 1:			//add new bus
					newBus(Buses, Drivers, Routes, locations);
					break;
				case 2:			//list all buses
					listBuses(Buses, Drivers, Routes, locations);
					break;
				case 3:			//search bus
					searchBus(Buses, Drivers, Routes, locations);
					break;
				case 4:			//update details of bus
					int updateBusNo;
					updateBus(Buses, Drivers, Routes, locations);
					break;
				case 5:			//delete bus
					deleteBus(Buses, Drivers, Routes);
					break;
				case 6:			//manage routes
					manageRoutes(Routes, locations, Buses);
					break;
				case 7:			//manage Drivers
					manageDrivers(Drivers, Buses);
					break;
				case 8:		//logOut
					break;
				}
			} while (adminMenuChoice != 8);
		}
		else if (option == 2){
			//general
			int generalMenuChoice;
			do{
				generalMenu();
				cout << "\t\tYour choice:"; cin >> generalMenuChoice;
				switch (generalMenuChoice){
				case 1://book a seat
					bookSeat(Buses, Routes, locations, Tickets);
					break;
				case 2://see booking details
					seeBookingDetails(Buses, Routes, locations, Tickets);
					break;
				case 3://cancel booking
					removeBooking(Buses, Routes, locations, Tickets);
					break;
				case 4://exit
					break;
				}
			} while (generalMenuChoice != 4);
		}
	} while (option != 3);
}