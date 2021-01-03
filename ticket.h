#include"bus.h"

struct ticket{
protected:
	static int nextID;
public:
	ticket(){
		ticketID = ++nextID;
	}
	int ticketID, busID;	//bus--->bus no, seat no, route(dept & dest location), timing
	std::vector<int>seatNos;//--->customer details can be found from seat of the bus

	//functions
	void enterData(int, std::vector<int>);
	void printTicket(std::vector<bus>, std::vector<location>, std::vector<route>);
};