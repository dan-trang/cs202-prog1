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

This class also creates the "shipping facilities"
physical location information. This will be used to
track the travel path of the order.
************************************************/
#include "location.h"
#include "order.h"

#include <iostream>
#include <cstring>

class transportation
{
public:
	transportation();
	transportation(order& src_order);
	transportation(const transportation& src_transportation);
	~transportation();

	//set functions
	void setNationalFacility(order& src_order, int shipping_method);	//sets large transport facility info, determined by shipping type + scale
	void setLocalFacility(order& src_order, int shipping_method);	//sets small transport facility info, takes incoming order and delivers to customer
    location* locationUpdate();     //updates 2nd order process location to local facility
	bool confirmArrived(location& userLocation);	//compares current package location and final destination address
	bool markArrived();		//returns true for arrived, will be used to finalize order
	bool shipOut();		//deploys ground/air vehicle, adds new location at arrival

private:
	char* _vehicle_name;		//internally defined
	char* _vehicle_type;		//internally defined
	int _travel_time;	//dependent on vehicle type
	order* transport_order;	//to be copied in from purchase Order received from Distro-Center
	location* transport_location;  //TBA dependant on national/local scale of facility
};