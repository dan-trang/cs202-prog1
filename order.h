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
#ifndef ORDER_H
#define ORDER_H
#include "location.h"
#include "product.h"

class order
{
public:
	order();
	//package and location will be set to an object before passing in
	order(char* customer_name, int selected_shipping, const product& order_product, const location& order_location);
	order(const order& src_order);	//copy constructor
	~order();

	void copy(const order& src_order);		//deep copy wrapper function
    package* passProduct();		//helper function to pass critical product info up the chain
    int getShippingMethod();   //this get function returns an integer that flags its shipping method
    void setShippingMethod(int flag);   //helper function to edit shipping method
	void calculateCost();	//displays total cost, calls product cost function
	void displayOrderDetails();		//displays details for internal use only
	void printInvoice(); 	//prints out Invoice statement for customer
    int findIndex();   //to return the int value based on order_package category
    bool compareName(product& src_product); //to call product comparison
    bool compareLocation(location& userLocation);	//product location comparison
    bool compareFull(product& src_product);	//full product to product comparison

private:
	void generateOrderID(); 	//generates a "random" order ID (have not implemented evenly distributed rand() number)
	int _order_ID;	//randomly generated unique ID, char* for c-string strcmp()
	char* _customer_name;	//set from input by Customer
	int _shipping_method;	//set from input by Customer (1.standard, 2.expedited, 3.overnight)
	package* order_package;		//User sets quantity of items to be purchased, final destination here
};
#endif
