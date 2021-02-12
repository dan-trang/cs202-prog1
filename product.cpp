/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Product Implementation File

Product class is conceptually the Node. It has a
next pointer which points to other Nodes in the list.
This class can set all values, copy, and display its
contents. The getNext() function is a wrapper function
that returns the next pointer by reference. Add and
Subtract functions will modify the quantity of the product
which will reflect the in-stock inventory of the Warehouse.
A Product class can build a LLL using its next pointers to 
build the links between Product Nodes.

Package class has two important pointers: head and tail.
The head and tail pointers will contruct the LLL for holding
location information. Since Package is a derived class of
Product, it is also a Node. The total travel path of this
object will be kept recorded in the LLL built using head
and tail pointers. This class can display current location
using tail, or full location starting at the head. The location
can be updated using the arrivedAt() function which will take
the current location and add it to the end of the list.
************************************************/
#include "product.h"
using namespace std;

//default constructor
product::product(): _product_name(nullptr), _category(nullptr), _product_ID(nullptr), _price(0.0), _quantity(0), product_location(nullptr), next(nullptr){}

//constructor with full arguments
product::product(char* product_name, char* category, char* product_ID, float price, int quantity): product_location(nullptr), next(nullptr)
{
	setName(product_name);
	setCategory(category);
	setProductID(product_ID);
	setPrice(price);
	setQuantity(quantity);
}

//empty product object w/ just location information
product::product(const location& src_location): _product_name(nullptr), _category(nullptr), _product_ID(nullptr), _price(0.0), _quantity(0), next(nullptr)
{
    product_location = new location(src_location);
}

//copy constructor
product::product(const product& src_product): next(nullptr)
{
    if(src_product.product_location != nullptr)
    {
        product_location = new location(*(src_product.product_location));
    }
    copy(src_product);
}

//conditional, and situational constructor that takes in a source product & location
product::product(const product& src_product, const location& src_location): next(nullptr)
{
    product_location = new location(src_location);
    copy(src_product);
}

//deconstructor 
product::~product()
{
	if(this->_product_name)
    {
		delete this->_product_name;
	    _product_name = nullptr;
    }

	if(this->_category)
    {
		delete this->_category;
	    _category = nullptr;
    }

	if(this->_product_ID)
    {
		delete this->_product_ID;
	    _product_ID = nullptr;
    }
    if(this->product_location)
    {
        delete product_location;
        product_location = nullptr;
    }
}


//Set function implementations
void product::setName(char* product_name)
{
	this->_product_name = new char[strlen(product_name)+1];
	strcpy(_product_name, product_name);
	return;
}

void product::setCategory(char* category)
{
	this->_category = new char[strlen(category)+1];
	strcpy(_category, category);
	return;
}

void product::setProductID(char* product_ID)
{
	this->_product_ID = new char[strlen(product_ID)+1];
	strcpy(_product_ID, product_ID);
	return;
}

void product::setPrice(float price)
{
	_price = price;
	return;
}

void product::setQuantity(int quantity)
{
	_quantity = quantity;
	return;
}

void product::setNext(location& new_location)
{
    this->next = new product(new_location);
    return;
}


//get wrapper function to return pointer by reference
product*& product::getNext()
{
    return this->next;
}


//returns an integer flag depending on product category (0.CPU, 1.GPU, 2.Motherboard)
int product::getCategory()
{
   if(strcmp(this->_category, "CPU") == 0)
       return 0;
   else if(strcmp(this->_category, "GPU") == 0)
       return 1;
   else if(strcmp(this->_category, "Motherboard") == 0)
       return 2;
   else
   {
       return 3;    //integer 3 will flag an undefined category
   }
}

//Adds a quantity integer to current quantity using incoming source product info
void product::addQuantity(product& src_product)
{
   _quantity += src_product._quantity; 
   return;
}

//Subtracts a quantity integer from current quantity using incoming source product info
void product::subtractQuantity(product& src_product)
{
    _quantity -= src_product._quantity;
    return;
}

//Builds the Linear Linked List of product nodes
bool product::addProduct(product& src_product)
{
    if(!next)   //if next ptr does not point to an existing node
    {
        next = new product(src_product); //create a new node here, [144 bytes lost]
        return true;
    }
    else
    {
        product* temp = next;   //unecessary temp pointer... 
        while(temp->compareName(src_product) == false  && temp->getNext() != nullptr)   //while not matching and not end of list
        {
            temp = temp->getNext(); //traverse to next in list
        }

        if(temp->compareName(src_product) == true) //if the product names are same
        {
            temp->addQuantity(src_product); //add source product's quantity to this quantity
            return true;
        } 
        else //we've reached the end of list == nullptr
        {
            temp->addProduct(src_product);
            return true;
        }
    }
}

//removes product by subtracting quantity
bool product::removeProduct(product& src_product)
{
    while(next->compareName(src_product) == false && next->next != nullptr)
    {
        this->next = next->getNext();
    }

    if(next->compareName(src_product) == true)  //found the comparable product
    {
        if(next->compare(src_product) == true)
        {
            next->subtractQuantity(src_product);  //subtract source product's quantity from this quantity
            cout<<"Order request fulfilled."<<endl;
            return true;
        }
        else //if quantity is not enough to fulfill order
        {
            cout<<"There's not enough ["<<_product_name<<"] inventory to fulfill order."<<endl;
            return false;
        }
        
        if(_quantity == 0) //if quantity hits zero, request restock
        {
            cout<<"Restocking needed for ["<<_product_name<<"]"<<endl;
            return false;
        }

        return true;
    }
    else   //reached end of the list == nullptr
    {
        cout<<"Could not find product in inventory"<<endl;
        return false;
    }
}

//copy helper functions which can be called as a stand-alone function
void product::copy(const product& src_product)
{
	this->_product_name = new char[strlen(src_product._product_name)+1];
	strcpy(_product_name, src_product._product_name);

	this->_category = new char[strlen(src_product._category)+1];
	strcpy(_category, src_product._category);

	this->_product_ID = new char[strlen(src_product._product_ID)+1];
	strcpy(_product_ID, src_product._product_ID);

	_price = src_product._price;
	_quantity = src_product._quantity;
    
    return;
}

//compares two product sources and returns a successful match or failed match, displays quantity availability
bool product::compare(const product& src_product) const
{
	if(strcmp(this->_product_name, src_product._product_name) != 0)
	{
		cout<<"[Product name does not match]"<<endl;
		return false;
	}

	if(strcmp(this->_category, src_product._category) != 0)
	{
		cout<<"[Product category does not match]"<<endl;
		return false;
	}

	if(strcmp(this->_product_ID, src_product._product_ID) != 0)
	{
		cout<<"[Product #ID does not match]"<<endl;
		return false;
	}

	if(_price != src_product._price)
	{
		cout<<"[Product pricing does not match]"<<endl;
		return false;
	}

	if(this->_quantity >= src_product._quantity)
	{
		cout<<"Current quantity ["<<this->_quantity<<"] is enough to fulfill order amount of ["<<src_product._quantity<<"]"<<endl;
		return true;
	}
	else
	{
		cout<<"Inventory is too low to fulfill purchase order..."<<endl;
		return false;
	}
}

//compares two source locations for succesful or failed match
bool product::compareLocation(location& src_location)
{
    bool check = product_location->compare(src_location);
    return check;
}

//compares ONLY the source product's names, situational
bool product::compareName(const product& src_product) const
{
    if(strcmp(this->_product_name, src_product._product_name) != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//displays a single Product information
void product::displayInfo()
{
        cout<<_product_name<<" SKU#"<<_product_ID<<"\n"<<_category<<"\n";
        cout<<"Price per unit: $"<<_price<<"\n"<<"Quantity: "<<_quantity<<"\n"<<endl;

	return;
}

//Calculates and displays the total cost
void product::displayCost() const
{
	float cost = (_quantity) * (_price);
	cout<<"Total Cost: $"<<cost<<endl;
}

//displays the Customer Entered information that is tagged to this Product
//not to be confused with Product shipping log (built by package head, tail pointers)
void product::displayLocation() const
{
    product_location->display();
    return;
}

//PACKAGE CLASS IMPLEMENTATION BELOW
//default constructor
package::package(): head(nullptr), tail(nullptr){}

//constructor with arguments, initialization list calls parent class Product Constructor
package::package(const product& src_product, const location& src_location): product(src_product, src_location), head(nullptr), tail(nullptr)
{
    //cout<<"Package Constructor called"<<endl;
}

//Package deconstructor cleans up shipping log LLL
package::~package()
{
    while(head != nullptr)
    {
        delete head;
        head = head->getNext();
    }
    tail = head = nullptr;
    //cout<<"PACKAGE DESTRUCTOR CALLED..."<<endl;
}

//Appends a new location node to the end of the shipping log LLL
void package::arrivedAt(location& src_location)
{
    //product* temp = new product(src_location);
    if(head == nullptr)
    {
       head = new product(src_location);
       tail = head;
    }
    else
    {
        tail->setNext(src_location);    
        tail = tail->getNext();
    }
    return;
}

//displays tail pointer location which is most recent
void package::displayCurrLocation()
{
    tail->displayLocation();	
}

//displays starting from head going to tail pointer
void package::displayTotalLocation()
{
    product* temp = head;
	while(temp->getNext() != nullptr)
	{
        temp->displayLocation();
        temp = temp->getNext(); 
	}
	temp->displayLocation();
	return;
}
