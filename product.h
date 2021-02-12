/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Product Header File

The Product class contains functions that can
set the details about the product and its travel
path throughout the distribution system. Package
class will act as a sort of Node that can be linked
with other Nodes to form a Linear Linked List.
Package class "is a" product, so it is derived and
inherits all public/protected members of Product.

************************************************/
#ifndef PRODUCT_H
#define PRODUCT_H
#include "location.h"

class product   //conceptually is a Node with *next and location data 
{
public:
	product();
	product(char* product_name, char* category, char* product_ID, float price, int quantity); //full args constructor
    product(const location& src_location); //just location copy
    product(const product& src_product);  //just product copy, location from source product
    product(const product& src_product, const location& src_location);
	~product();

	//set functions provide editting power to those with access to its public
	void setName(char* product_name);
	void setCategory(char* category);
	void setProductID(char* product_ID);
	void setPrice(float price);
	void setQuantity(int quantity);

    //helper functions to get/set next pointer
    void setNext(location& new_location);
    product*& getNext();

    int getCategory();   //get function to communicate what kind of category type this item is
    void addQuantity(product& src_product);   //adds quantity
    void subtractQuantity(product& src_product);   //subtracts quantity

    bool addProduct(product& src_product);    //creates new product node with product info
    bool removeProduct(product& src_product); //deletes product node based on matching name

	void copy(const product& src_product);		//helper function to deep copy dynamic memory
	bool compare(const product& src_product) const;		//compares two product's name, ID, and quantity
	bool compareLocation(location& src_location);
    bool compareName(const product& src_product) const;     //compares just product's Names
	void displayInfo();		//displays all of the Product's details
	void displayCost() const;
    void displayLocation() const; //displays location info tagged to this object
	
protected:
	char* _product_name;
	char* _category;
	char* _product_ID;
	float _price;
	int _quantity;	//to be defined by User input
	location* product_location; //initialized internally in .cpp to New Orders/Packaging Facility
    product* next;  //next ptr used by LLL
};

class package: public product 	//package conceptually is the LLL data structure, Shipping Tracker + Category Products
{
public:
	package();
    package(const product& src_product, const location& src_location);
	~package();

    product* getTail(); //same function as getNext() in product..
    
	void arrivedAt(location& src_location);   //create new product node with location	
	void displayCurrLocation();		//displays end "node" as the current location of the Product
	void displayTotalLocation();	//recursively display all "node" locations

protected:
    product* head;
    product* tail;
};
#endif
