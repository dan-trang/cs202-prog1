/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Distribution Header File

The Distribution class is the Brain of the program.
It will contain objects from multiple classes to
manage its own inventory, shipping the product, and
marking the order form for completion. 

************************************************/
#include "product.h"
#include "order.h"
#include "location.h"

class distribution
{
public:
	distribution();
	distribution(char* scale, int capacity);
	distribution(const distribution& src_distribution);		//will need to deep copy two data structures
															//one for Product List and one for Order List
	~distribution();	//take care to deallocate dynamic memory & data structures

	void setScale(char* scale);     //change to National or Local scale
	void setCapacity(int capacity);		//dependent on Scale

	bool addProduct(product& src_product);	//adds product quantity to existing data structure or
											//creates new Node in list if none exist already
	bool removeProduct(product& src_product);	//subtract product quantity, if hits zero, delete node
	bool checkAvailable(product& src_product);	//check if existing quantity fulfills purchase order quantity
	void restock(product& src_product);		//if quantity hits low threshold, request for restocking
	void displayInventory(product** product_list[]);	//recursively display all product name/quantity

private:
	char* _scale;	//to be National or Local scale
	int _capacity; 	//capacity to hold product
	product** product_list[];	//array of category elements, each pointing to LLL of product items
	order* order_list[];	//array of 3 priority elements, each pointing to array of Order objects 
							//to hold multiple purchase requests in stack/queue... Ambitious?
	location distro_location;
	transportation distro_transportation;
};