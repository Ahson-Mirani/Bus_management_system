#include"person.h"

class date{
public:
	int day, month, year;
	date(){}
	date(int d, int m, int y){ day = d; month = m; year = y; }
	//define its output feature---->operator overloading through frind function
	friend std::ostream& operator<<(std::ostream& os, const date& d){
		os << d.day << "/" << d.month << "/" << d.year;
		return os;
	}
	void setdate();
};

class mytime{
public:
	int hours, minutes, seconds;
	mytime(){}
	mytime(int h, int m, int s){
		hours = h; minutes = m; seconds = s;
	}
	//define its output feature
	friend std::ostream& operator<<(std::ostream& os, const mytime& t){
		os << t.hours << ":" << t.minutes << ":" << t.seconds;
		return os;
	}
	//define its input feature
	void setTime();
};

class seat{
public:
	seat(){//by default first 10 seats are business class and rest are economy class
		setStandard();
	}
	person customer;
	int seatNo;
	bool isBusiness;
	bool isOccupied = false;

	void book();
	void printDetails();
	void setStandard();
	void unBook();
};

void locate(int, int);