/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Order Implementation File

Builds the purchase order object. Contains critical
informtation about the purchase request, product
information, and final destination of shipping.
Important compare functions are necessity to validate
correct order is being shipped from-and-to different
facilities. Generate Order ID for now is static. It can
be upgraded to a number generator algorithm to your liking.
************************************************/
#include "order.h"
#include <iomanip>
using namespace std;

order::order(): _order_ID(0), _customer_name(nullptr), _shipping_method(0), order_package(nullptr){
    //cout<<"Order Default constructor called."<<endl;
}

order::order(char* customer_name, int selected_shipping, const product& order_product, const location& order_location): order_package(nullptr)
{
	generateOrderID();
	this->_customer_name = new char[strlen(customer_name)+1];
	strcpy(_customer_name, customer_name);

	_shipping_method = selected_shipping;

	order_package = new package(order_product, order_location);
    //cout<<"Order Constructer w/Args"<<endl;
}

order::order(const order& src_order)
{
	copy(src_order);
}

order::~order()
{
	if(_customer_name)
	{
		delete[] this->_customer_name;
        _customer_name = nullptr;
	}

	delete order_package;
	//cout<<"ORDER DESTRUCTOR CALLED..."<<endl;
}

//I have not implemented an evenly distributed randomized number system yet (plug random num algorithm here)
void order::generateOrderID()
{
    _order_ID = 9999999;   //for now a static cool number
}

//copy helper function, can be called as a stand-alone
void order::copy(const order& src_order)
{
    _order_ID = src_order._order_ID;

	this->_customer_name = new char[strlen(src_order._customer_name)+1];
	strcpy(_customer_name, src_order._customer_name);

	_shipping_method = src_order._shipping_method;

    order_package = new package(*(src_order.order_package));
	return;
}

//helps passes package information up the chain
package* order::passProduct()
{
    return this->order_package;
}

//flags the shipping method with an integer
int order::getShippingMethod()
{
    return this->_shipping_method;
}

//returns the shipping integer flag
void order::setShippingMethod(int flag)
{
    this->_shipping_method = flag;
    return;
}

//calls product cost function to return total cost
void order::calculateCost()
{
	order_package->displayCost();
	return;
}

//To be used internally only, you can print this out to customer if they wanted
void order::displayOrderDetails()
{
	cout<<"\nOrder #"<<_order_ID<<"\n";
	cout<<"Name: "<<_customer_name<<"\n";
	cout<<"Product Info: "<<endl;
    order_package->displayInfo();
	cout<<"Ship To: "<<endl;
    order_package->displayLocation();
    cout<<"Shipping: ";
    if(_shipping_method == 1)
        cout<<"Standard"<<endl;
    else if(_shipping_method == 2)
        cout<<"Expedited"<<endl;
    else if(_shipping_method == 3)
        cout<<"Overnight"<<endl;
    else
    {
        cout<<"UNDEFINED"<<endl;
    }
	return;
}

//user-friendly display to show end customer the final receipt
void order::printInvoice()
{
    cout<<"---------------------------------------------"<<endl;
    cout<<"CS202 PDX WHOLESALE ELECTRONICS & COMPUTERS  |"<<endl;
    cout<<"1825 SW Broadway, Portland, OR 97201         |"<<endl;
    cout<<"pdxbestcomputers.com                         |"<<endl;
    cout<<"(800)547-8887                                |"<<endl;
    cout<<"---------------------------------------------|"<<endl;
    cout<<"BILL TO:"<<endl;
    cout<<_customer_name<<"\tOrder #"<<_order_ID<<endl;
    order_package->displayLocation(); 
    order_package->displayInfo();
    calculateCost();
    cout<<"\nThank you for doing business with us!!"<<endl;
    return;
}

//finds an integer based on category, helps insert order in the array data structure
int order::findIndex()
{
    int returnIndex = order_package->getCategory();
    return returnIndex;
}

//compare functions below
bool order::compareName(product& src_product)
{
    bool checkReturn = order_package->compareName(src_product);    
    return checkReturn;
}

bool order::compareLocation(location& userLocation)
{
    bool checkReturn = order_package->compareLocation(userLocation);
    return checkReturn;
}

bool order::compareFull(product& src_product)
{
    bool checkReturn = order_package->compare(src_product);    
    return checkReturn;
}
