/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Location Implementation File

This file implements the constructors, destructor,
and functions of Location class. These functions
include handle setting all the values of a location
object as well as the ability to copy from another
source.
************************************************/
#include "location.h"
#include <iostream>
using namespace std;

location::location(): _location_name(nullptr), _street(nullptr), _state(nullptr), _zip(0){}

location::location(char* location_name, char* street, char* state, int zip)
{
	this-> _location_name = new char[strlen(location_name)+1];
	strcpy(_location_name, location_name);

	this-> _street = new char[strlen(street)+1];
	strcpy(_street, street);

	this-> _state = new char[strlen(state)+1];
	strcpy(_state, state);

	_zip = zip;
    //cout<<"Location Constructor w/Args called"<<endl;
}

location::location(const location& src_location)
{
 	copy(src_location);
    //cout<<"Location Copy Constructor called"<<endl;
}

location::~location()
{
	if(_location_name)
    {
		delete[] _location_name;
	    _location_name = nullptr;
    }

	if(_street)
    {
		delete[] this->_street;
	    _street = nullptr;
    }

	if(_state)
    {
		delete[] this->_state;
	    _state = nullptr;
    }
    
    //cout<<"LOCATION DESTRUCTOR CALLED..."<<endl;
}

void location::setName(char* location_name)
{
    this->_location_name = new char[strlen(location_name)+1];
    strcpy(_location_name, location_name);
}

void location::setAddress(char* street, char* state, int zip)
{
    this->_street = new char[strlen(street)+1];
    strcpy(_street, street);

    this->_state = new char[strlen(state)+1];
    strcpy(_state, state);

    _zip = zip;
}


void location::copy(const location& src_location)
{
    this->_location_name = new char[strlen(src_location._location_name)+1];
    strcpy(_location_name, src_location._location_name);

    this->_street = new char[strlen(src_location._street)+1];
    strcpy(_street, src_location._street);

    this->_state = new char[strlen(src_location._state)+1];
    strcpy(_state, src_location._state);

    _zip = src_location._zip;

	return;
}

bool location::compare(const location& src_location) const
{
	if(strcmp(this->_location_name, src_location._location_name) != 0)
	{
		cout<<"[Location Name does not match]"<<endl;
		return false;
	}

	if(strcmp(this->_street, src_location._street) != 0)
	{
		cout<<"[Location street does not match]"<<endl;
		return false;
	}

	if(strcmp(this->_state, src_location._state) != 0)
	{
		cout<<"[Location state does not match]"<<endl;
		return false;
	}

	if(this->_zip != src_location._zip)
	{
		cout<<"[Location Zip Code does not match]"<<endl;
		return false;
	}

	return true;
}

void location::display() const
{
    cout << "-----------------------------" << endl;
	cout << _location_name <<"\n"<< _street <<"\n"<< _state <<", "<< _zip << endl;
    cout.clear();
    cout << "-----------------------------"<<endl;
    return;
}
