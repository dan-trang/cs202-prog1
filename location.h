/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Location Header File

This file prototypes the construction and management
of Location objects. Useful functions include updating
new location information, making a deep copy from a
passed in source location object, comparing two locations,
and displaying all location information for readibility.
To be used by Product/Order/Distribution class.

************************************************/
#include <iostream>
#include <cstring>

class location
{
public:
	location();
	location(char* location_name, char* street, char* state, int zip);	//constructor with args
	location(const location& src_location); 	//copy constructor
	~location();

    //set functions
    void setName(char* location_name);
    void setAddress(char* street, char* state, int zip);

	void copy(const location& src_location); 	//takes in object of type location and makes deep copy
	bool compare(const location& src_location) const; 	//return true if src location and curr location are same
	void display() const; 	//displays full location

private:
	char* _location_name;
	char* _street;
	char* _state;
	int _zip;
};
