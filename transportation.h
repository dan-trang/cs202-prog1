/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Transportation Header File

The Transportation class handles both ground and
air shipping which will be determined by the type
of shipping method as listed in the order form.
This class will communicate travel time and arrival
of the package to its final destination -- marking
the end of the journey of the package and ultimately
fulfulling the order.

************************************************/
#include <iostream>
#include <cstring>

class transportation
{
public:
	transportation();
	transportation(const transportation& src_transportation);
	~transportation();

	//set functions
	void setVehicle(char* vehicle);		//sets vehicle type based on priority of shipping
	void setTravelTime(int travel_time); //dependent on vehicle type

	int calculateTime(order& transport_order);    //returns estimated total shipping time in #days
	bool groundShipping(order& transport_order);		//deploys ground vehicle, adds new location arrival
	bool airShipping(order& transport_order);		//deploys aircraft, adds new location arrival

	bool checkReceived(order& transport_order);	//check that package is received from Distro-Center,
							//and purchase order == shipping order details are exactly same

	bool checkArrived(order& transport_order);	//compares current package location and final destination address
							//returns 'true' when package has arrived at final destination

	int markArrived();		//returns 1' for arrived, will be used to break out of logic and
							//finalize the Order

private:
	char* _vehicle;		//internally defined
	int _travel_time;	//dependent on vehicle
	order transport_order;	//to be copied from purchase Order received from Distro-Center
};