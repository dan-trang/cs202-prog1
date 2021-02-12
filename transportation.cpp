/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Transportation Implementation File

This file implements the transportation functions.
Transportation is not only the vehicle type and name,
but also the physical address and location of the
facility that receives and ships out the orders.

The "set facility" functions determine the location
based on what is needed by the order. Scale can be
national or local, and vehicle is determined to suit
whats best for the purchase order. This location can
be read-in from a file to test different locations.
************************************************/
#include "transportation.h"
using namespace std;

transportation::transportation(): _vehicle_name(nullptr), _vehicle_type(nullptr), _travel_time(0), transport_order(nullptr), transport_location(nullptr)
{
	cout<<"Transportation Default Constructor Called."<<endl;
}

//Creates a transportation facility based on order shipping method needs
transportation::transportation(order& src_order)
{
	if(src_order.getShippingMethod() == 1)
	{
		setNationalFacility(src_order, 1);	//national large facility with standard ground shipping
	}
	else if(src_order.getShippingMethod() == 2)
	{
		setLocalFacility(src_order, 1);	//local small facility with expedited ground shipping
	}
	else if(src_order.getShippingMethod() == 3)
	{
		setNationalFacility(src_order, 2);	//national large facility with overnight air shipping
	}
	else if(src_order.getShippingMethod() == 4)	//can only be flagged 4 after passing through transport once
	{
		setLocalFacility(src_order, 2);	//local facility receives from national facility
	}
	else
	{
		cout<<"[Undefined shipping method]"<<endl;
	}
}

//copy constructor
transportation::transportation(const transportation& src_transportation)
{
	this->_vehicle_name = new char[strlen(src_transportation._vehicle_name)+1];
	strcpy(_vehicle_name, src_transportation._vehicle_name);

	this->_vehicle_type = new char[strlen(src_transportation._vehicle_type)+1];
	strcpy(_vehicle_type, src_transportation._vehicle_type);

	_travel_time = src_transportation._travel_time;

	transport_order = new order(*(src_transportation.transport_order));

	transport_location = new location(*(src_transportation.transport_location));
}

//transportation deconstructor
transportation::~transportation()
{
	if(_vehicle_name != nullptr)
	{
		delete _vehicle_name;
		_vehicle_name = nullptr;
	}

	if(_vehicle_type != nullptr)
	{
		delete _vehicle_type;
		_vehicle_type = nullptr;
	}

	if(transport_order != nullptr)
	{
		delete transport_order;
	}
	
	if(transport_location != nullptr)
	{
		delete transport_location;
	}
}

//creates national facility information, this can be "dynamically" created using a read-in file
void transportation::setNationalFacility(order& src_order, int shipping_method)
{
	int zip, MAX_CHAR = 100;
	char location_name[MAX_CHAR], street[MAX_CHAR], state[MAX_CHAR], vehicle_type[MAX_CHAR], vehicle_name[MAX_CHAR]; 
	if(shipping_method == 1)	//set standard ground facility
	{
		//setting vehicle
		strcpy(vehicle_type, "Semi-Truck");
		strcpy(vehicle_name, "Kenworth T680 Advantage");
		this->_vehicle_name = new char[strlen(vehicle_name)+1];
		strcpy(this->_vehicle_name, vehicle_name);
		this->_vehicle_type = new char[strlen(vehicle_type)+1];
		strcpy(this->_vehicle_type, vehicle_type);
		this->_travel_time = 4;	//in days

		//initializing national address
		strcpy(location_name, "ECO-ROUTE National Ground Shipping Facility");
		strcpy(street, "502 W 42nd St, New York");
		strcpy(state, "NY");
		zip = 10036;

		transport_order = new order(src_order);
		transport_location = new location(location_name, street, state, zip);
		return;
	}

	if(shipping_method == 2)	//set overnight air facility
	{
		//setting vehicle
		strcpy(vehicle_type, "Cargo Plane");
		strcpy(vehicle_name, "Boeing 747");
		this->_vehicle_name = new char[strlen(vehicle_name)+1];
		strcpy(this->_vehicle_name, vehicle_name);
		this->_vehicle_type = new char[strlen(vehicle_type)+1];
		strcpy(this->_vehicle_type, vehicle_type);
		this->_travel_time = 1; //in days

		//initializing national address
		strcpy(location_name, "ECO-ROUTE National Air Shipping Facility");
		strcpy(street, "6 North Boundary Rd, Queens");
		strcpy(state, "NY");
		zip = 11430;

		transport_order = new order(src_order);
		transport_location = new location(location_name, street, state, zip);
		return;
	}
}
	
//creates the Local shipping facility information, this can be "dynamically" set by a read-in file
void transportation::setLocalFacility(order& src_order, int shipping_method)
{
	int zip, MAX_CHAR = 100;
	char location_name[MAX_CHAR], street[MAX_CHAR], state[MAX_CHAR], vehicle_type[MAX_CHAR], vehicle_name[MAX_CHAR]; 

	if(shipping_method == 1)	//set expedited ground facility
	{
		//setting vehicle
		strcpy(vehicle_type, "Package Van");
		strcpy(vehicle_name, "Ram ProMaster 3500");
		this->_vehicle_name = new char[strlen(vehicle_name)+1];
		strcpy(this->_vehicle_name, vehicle_name);
		this->_vehicle_type = new char[strlen(vehicle_type)+1];
		strcpy(this->_vehicle_type, vehicle_type);
		this->_travel_time = 2; //in days

		//initializing local address
		strcpy(location_name, "ECO-ROUTE Local Shipping Facility");
		strcpy(street, "9601 NE Alderwood Rd, Portland");
		strcpy(state, "OR");
		zip = 97220;

		transport_order = new order(src_order);
		transport_location = new location(location_name, street, state, zip);
		return;
	}

	if(shipping_method == 2)	//express, receiving facility
	{
	//setting vehicle
		strcpy(vehicle_type, "VIP Van");
		strcpy(vehicle_name, "Mercedes-Benz Sprinter 2500");
		this->_vehicle_name = new char[strlen(vehicle_name)+1];
		strcpy(this->_vehicle_name, vehicle_name);
		this->_vehicle_type = new char[strlen(vehicle_type)+1];
		strcpy(this->_vehicle_type, vehicle_type);
		this->_travel_time = 0; // < less than a day

		//initializing local address
		strcpy(location_name, "ECO-ROUTE Local Shipping Facility");
		strcpy(street, "9601 NE Alderwood Rd, Portland");
		strcpy(state, "OR");
		zip = 97220;

		transport_order = new order(src_order);
		transport_location = new location(location_name, street, state, zip);
		return;	
	}
}

//updates the location of package IF it gets delivered to a 2nd facility
location* transportation::locationUpdate()
{
    int MAX_CHAR = 100;
   	char location_name[MAX_CHAR], street[MAX_CHAR], state[MAX_CHAR]; 

    location* newLocation;
    //initializing local address address
    strcpy(location_name, "ECO-ROUTE Local Shipping Facility");
    strcpy(street, "9601 NE Alderwood Rd, Portland");
    strcpy(state, "OR");
    int zip = 97220;

    newLocation = new location(location_name, street, state, zip);
    return newLocation;
}

//compares and validates final destination is delivered destination
bool transportation::confirmArrived(location& userLocation)
{
	bool arrived = transport_order->compareLocation(userLocation);
	return arrived;
}

//marks arrival with a boolean value, breaks any looping logic
bool transportation::markArrived()
{
	cout<<"Package arriving at customer location..."<<endl;
	return true;
}

//executes the fulfillment of the shipping order
bool transportation::shipOut()
{
	if(transport_order->getShippingMethod() == 4)
	{
        char yesNo;
		transport_order->passProduct()->arrivedAt(*locationUpdate());
		markArrived(); //no structural use for bool checker here
        transport_order->printInvoice(); //display for end customer
        cout<<"Would you like to see the shipping tracker log? (y/n): "; //optional 
        cin>>yesNo;
        if(yesNo == 'y' || yesNo == 'Y')
        {
            transport_order->passProduct()->displayTotalLocation();
            transport_order->passProduct()->displayLocation();
        }
        return true;
	}
	else
	{
		transport_order->passProduct()->arrivedAt(*transport_location);
		transport_order->setShippingMethod(4);
        shipOut();  //shipping process again to next local shipping facility
	}
	return true;
}




