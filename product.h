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
#include "location.h"

class product
{
public:
	product();
	product(char* product_name, char* category, char* product_ID, float price, int quantity); //full args constructor
	product(const product& src_product);	//product copy constructor
	~product();

	//set functions provide editting power to those with access to its public
	void setName(char* product_name);
	void setCategory(char* category);
	void setProductID(char* product_ID);
	void setPrice(float price);
	void setQuantity(int quantity);

	void copy(const product& src_product);		//helper function to deep copy dynamic memory
	bool compare(const product& src_product) const;		//compares two product's name, ID, and quantity
	void displayInfo() const;		//displays all of the Product's details
	
protected:
	char* _product_name; //initialized internally
	char* _category;	//initialized internally
	char* _product_ID;	//initialized internally
	float _price;		//initialized internally
	int _quantity;	//to be defined by User input
	
};

class package: public product 	//package conceptually is a Node
{
public:
	package();

	void displayCurrLocation(const package& src_package) const;		//displays end "node" as the current location of the Product
	void displayTotalLocation(const package& src_package) const;	//recursively display all "node" locations
private:
	location product_location; //initialized internally in .cpp to New Orders/Packaging Facility
	package* next; //next pointer
};

