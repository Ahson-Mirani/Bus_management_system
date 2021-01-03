#include"seat.h"

int nooOfDigits(int num){
	if (num == 0){ return 0; }
	else{ return 1 + nooOfDigits(num /= 10); }
}
void printSpaces(int n){
	for (int i = 0; i < n; i++){
		std::cout << " ";
	}
}
void backSpaces(int n){
	for (int i = 0; i < n; i++){
		std::cout << "\b";
	}
}

void date::setdate(){
	locate(0, 7); std::cout << "\t\tDay:"; std::cin >> day;
	while (day <= 0 || day > 31){
		locate(0, 7); std::cout << "\t\tDay:"; printSpaces(nooOfDigits(day)); backSpaces(nooOfDigits(day)); std::cin >> day;
	}
	locate(0, 8);	std::cout << "\t\tMonth:"; std::cin >> month;
	while (month <= 0 || month > 12){
		locate(0, 8); std::cout << "\t\tMonth:"; printSpaces(nooOfDigits(month)); backSpaces(nooOfDigits(month)); std::cin >> month;
	}
	locate(0, 9); std::cout << "\t\tyear:"; std::cin >> year;
	while (year <= 0){
		locate(0, 9); std::cout << "\t\tYear:"; printSpaces(nooOfDigits(year)); backSpaces(nooOfDigits(year)); std::cin >> year;
	}
}

void mytime::setTime(){
	locate(0, 8);	std::cout << "\t\tHours:"; std::cin >> hours;
	while (hours < 0 || hours > 24){
		locate(0, 8); std::cout << "\t\tHours:"; printSpaces(nooOfDigits(hours)); backSpaces(nooOfDigits(hours)); std::cin >> hours;
	}
	locate(0, 9); std::cout << "\t\tMinutes:"; std::cin >> minutes;
	while (minutes < 0 || minutes > 60){
		locate(0, 9); std::cout << "\t\tMinutes:"; printSpaces(nooOfDigits(minutes)); backSpaces(nooOfDigits(minutes)); std::cin >> minutes;
	}
	locate(0, 10); std::cout << "\t\tSeconds:"; std::cin >> seconds;
	while (seconds <= 0 || seconds > 60){
		locate(0, 10); std::cout << "\t\tSeconds:"; printSpaces(nooOfDigits(seconds)); backSpaces(nooOfDigits(seconds)); std::cin >> seconds;
	}
}

void seat::printDetails(){
	if (isOccupied){
		std::cout << "\n\n\t\t\tDetails:\n\tName:" << customer.name;
		std::cout << "\n\t\tGender:" << customer.gender;
		std::cout << "\n\t\tAge:" << customer.age;
		std::cout << "\n\t\tCNIC:" << customer.CNIC;
		std::cout << "\n\tStandard:"; if (isBusiness) std::cout << "Business Class\n"; else{ std::cout << "Economy Class\n"; }
	}
	else{
		std::cout << "\n\n\t\tSeat is not occupied\n";
		std::cout << "\t\tStandard:"; if (isBusiness){ std::cout << "Business Class\n"; }
		else{ std::cout << "Economy Class\n"; }
	}
}

void seat::book(){
	std::cout << "Please enter following details:\n\tName:"; std::cin >> customer.name;
	std::cout << "\tGender:"; std::cin >> customer.gender;
	std::cout << "\tAge:"; std::cin >> customer.age;
	std::cout << "\tCNIC:"; std::cin >> customer.CNIC;
	isOccupied = true;
	std::cout << "Seat is booked.\n";
}

void seat::unBook(){
	std::string n;
	customer.name = n;
	customer.gender = -1;
	customer.age = -1;
	customer.CNIC = -1;
	isOccupied = false;
}

void seat::setStandard(){
	if (seatNo > 10){
		isBusiness = false;
	}
	else{
		isBusiness = true;
	}
}