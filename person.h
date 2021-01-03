#include<iostream>
#include<string>
#include<vector>
#include<windows.h>

int nooOfDigits(int num);
void printSpaces(int n);
void backSpaces(int n);

enum GENDER{ MALE, FEMALE };

class person{
public:
	std::string name;
	int gender;
	long long CNIC;
	int age;

	void printPerson(int spaces){
		printSpaces(spaces); std::cout << "NAME: " << name;
		printSpaces(spaces); std::cout << "GENDER: "; if (gender){ std::cout << "Female"; }
		else{ std::cout << "Male"; }
		printSpaces(spaces); std::cout << "CNIC: " << CNIC;
		printSpaces(spaces); std::cout << "AGE: " << age << "\n";
	}
};