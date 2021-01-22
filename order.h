/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Order Header File

The Order class will handle purchase details such
as quantity of products, type of product, final
destination for package, as well as useful info
for internal use like Order #ID and shipping method.

************************************************/
#include "location.h"

class order
{
public:
	order();
	order(char* customer_name, int selected_shipping);	//construct args passed-in by user
	order(const order& src_order);	//copy constructor
	~order();

	void setCustomer(char* customer_name);		//customer name can be editted
	void setShippingMethod(int selected_shipping);	//1.standard, 2.expedited, 3.overnight
	void copy(const order& src_order);		//deep copy helper function

	int calculateCost(const package& order_package);	//returns total cost
	void displayOrderDetails();		//displays details for internal use only
	void printInvoice(); 	//prints out Invoice statement for customer

private:
	void generateOrderID(); 	//generates and sets random, unique ID for purchase order
	char* _order_ID;	//randomly generated unique ID
	char* _customer_name;	//set from input by Customer
	int _shipping_method;	//set from input by Customer (1.standard, 2.expedited, 3.overnight)
	location order_destination;		//User sets final destination, goes here
	package order_package;		//User sets quantity of items to be purchased, goes here
};

