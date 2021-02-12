/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Distribution Header File

The Distribution class is the Brain of the program.
It will contain objects from multiple classes to
manage its own inventory, shipping the product, and
marking the order form for completion. The distribution
class will call the trasportation object to finalize
and ship out the order to the end customer.

************************************************/
#include "product.h"
#include "order.h"
#include "location.h"
#include "transportation.h"
#include <fstream>

class distribution
{
public:
	distribution();
	distribution(char* scale);
	distribution(const distribution& src_distribution);		//will need to deep copy two data structures
															//one for Inventory and one for Order DB
	~distribution();	//take care to deallocate dynamic memory & data structures

	void defineNational();     //sets parameters to National Distribution Center
	void defineLocal();		//sets parameters to Local Distribution Center
	void copyInventory(product** src_inventory);	//copies src_distribution.inventory
	void copyOrderDB(order** src_orderDB);	//copies src_distribution.orderDB

	bool addOrder(order& src_order);	//adds new purchase order to Order DataBase
	bool removeOrder(order& temp_order);		//removes order from DB
	bool shipOrder();	//executes the fulfillment of an Order (remove from orderDB, subtract product quantity)
	bool addProduct(product& src_product);	//adds product quantity to existing data structure or
											//creates new Node in list if none exist already
	bool removeProduct(product& src_product);	//subtract product quantity, if hits zero, delete node
	bool checkAvailable(order& src_order);	//check if existing quantity fulfills purchase order quantity
	void restock(product& src_product);		//if quantity hits low threshold, request for restocking
	void displayInventory();	//displays  all product name/quantity
    void displayOrders() const;   //displays all orders
	int findIndex(order& src_order); 	//helper function to find index#, returns index int
    int findIndex2(product& src_product);    //same as findIndex but for product objects
	int findPriority(order& src_order);		//helper function to find shipping priority, returns priority int

	void loadFromFile(const char* fileName);	//to load data from external file, will populate inventory

private:
	char* _scale;	//to be National or Local scale
	int orderDB_width;
    int array_size;
	product** inventory;	//array of category elements, each pointing to LLL of product items
	order** orderDB;	//linear array of pointers to order objects, using formula HOB[y * row_width + x] to access
				    	//column (x) at row (y) = 3 representing the 3 priorities of shipping
	location* distro_location;
	transportation* distro_transportation;
};
