/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Distribution Implementation File

The two main data structures contained in here is
the array of pointers to linked lists and the linear
array using a formula (y * width + x) to find position
as if it were a 2D array. 

This class can create the physical distribution facility
location, information, and hold product and order objects.
The loadFromFile() function can read in any text file with
the product data to populate the Inventory list.
************************************************/
#include "distribution.h"
using namespace std;

distribution::distribution(): _scale(nullptr), orderDB_width(0), inventory(nullptr), orderDB(nullptr), distro_location(nullptr)
{
	//cout<<"Distribution Default Constructor Called... Yikes"<<endl;
}//distro_transportation(nullptr)

distribution::distribution(char* scale)
{
	this->_scale = new char[strlen(scale)+1];
	strcpy(_scale, scale);

	if(strcmp(scale, "national") == 0)
	{
		defineNational();
	}
	else if(strcmp(scale, "local") == 0)
	{
		defineLocal();
	}
	else
	{
		cout<<"UNDEFINED SCALE"<<endl;
	}
	//cout<<"Distribution Constructor called..."<<endl;
}

distribution::distribution(const distribution& src_distribution)
{
	this->_scale = new char[strlen(src_distribution._scale)+1];
	strcpy(_scale, src_distribution._scale);

	copyInventory(src_distribution.inventory);
	copyOrderDB(src_distribution.orderDB);

	distro_location = new location(*(src_distribution.distro_location));
	//distro_transportation = new transportation(*(src_distribution.distro_transportation));
	//cout<<"Distribution Copy Constructor called..."<<endl;
}

distribution::~distribution()
{
	if(this->_scale)
	{
		delete[] this->_scale;
		_scale = nullptr;
	}

	if(this->inventory != nullptr)
	{
		for(int i=0; i<3; i++)
		{
			if(inventory[i] != nullptr)
				delete inventory[i];
		}
		delete[] inventory;
	}

	if(this->orderDB != nullptr)
	{
        for(int i=0; i<array_size; i++)
        {
            if(orderDB[i] != nullptr)
                delete orderDB[i];
        }
		delete[] orderDB;
	}

	delete distro_location;
	//delete distro_transportation;

	//cout<<"Distribution Destructor Called..."<<endl;
}

void distribution::defineNational()
{
	//I statically define these parameters, but very well can implement a loadFromFile for this too.
	int zip = 11234, MAX_CHAR = 50; //travel_time = 0;
    this->orderDB_width = 10;  //limited capacity for national warehouse
    this->array_size = 3 * orderDB_width; //3 represents priorities, width is capacity of each "queue"
	char location_name[MAX_CHAR], street[MAX_CHAR], state[MAX_CHAR]; //vehicle[MAX_CHAR];

    //building the inventory shell
	inventory = new product*[3];	//3 represents the categories (CPU, GPU, Motherboard)
	for(int i=0; i<3; i++)
		inventory[i] = nullptr;
    //build the order list 
	orderDB = new order* [array_size];

    //setting location of this distribution warehouse
	strcpy(location_name, "National Distribution Warehouse");
	strcpy(street, "1850 Ultica Ave, Brooklyn");
	strcpy(state, "NY");
	distro_location = new location(location_name, street, state, zip);

	//strcpy(vehicle, "TBA");		//National can be both Air/Ground. To be determined.
	//distro_transportation(vehicle, travel_time);
	return;
}

void distribution::defineLocal()
{
	//I statically define these parameters, but very well can implement a loadFromFile for this too.
	int zip = 97218, MAX_CHAR = 50; //travel_time = 2;
	this->orderDB_width = 3;  //limited capacity of this warehouse
    this->array_size = 3 * orderDB_width;
	char location_name[MAX_CHAR], street[MAX_CHAR], state[MAX_CHAR]; //vehicle[MAX_CHAR];

    //building the inventory
	inventory = new product*[3];	//3 represents the categories (CPU, GPU, Motherboard)
	for(int i=0; i<3; i++)
		inventory[i] = nullptr;

    //building order list
	orderDB = new order* [array_size];	//3 represents the priorities (standard,expedited,overnight)

    //setting location of this warehouse
	strcpy(location_name, "Local Distribution Warehouse");
	strcpy(street, "6722 NE Columbia Blvd, Portland");
	strcpy(state, "OR");
	distro_location = new location(location_name, street, state, zip);

	//strcpy(vehicle, "Commercial Van");	   //Local can only transport with medium-size Vans
	//distro_transportation(vehicle, travel_time);
	return;
}

void distribution::copyInventory(product** src_inventory)
{
	//implementing a copy algorithm for an array of pointers to Linked Lists...
	cout<<"Painfully thinking of solution here...."<<endl;
	return;
}

void distribution::copyOrderDB(order** src_orderDB)
{
	this->orderDB = new order* [array_size];
	for(int i=0; i<array_size; i++)
	{
		orderDB[i]->copy(*src_orderDB[i]);  //calls Order copy function, receives order address. Working???   
	}
	return;
}

int distribution::findPriority(order& src_order)
{
	if(src_order.getShippingMethod() == 1)
		return 0;

	else if(src_order.getShippingMethod() == 2)
		return 1;

	else if(src_order.getShippingMethod() == 3)
		return 2;

	else
	{
		return 3;
	}
}

bool distribution::addOrder(order& src_order)
{
	int position = 0;	//used to access orderDB[] by position value
	int priority = findPriority(src_order);
	if(priority == 3)
	{
		cout<<"UNDEFINED SHIPPING METHOD... FAILED TO ADD ORDER"<<endl;
		return false;
	}
	//accesses position by priority formula AND as long as position value does not exceed width of "queue"
	while(orderDB[priority * orderDB_width + position] != nullptr && (position < orderDB_width))
	{
		position++;
	}

	if(position == orderDB_width)
	{
		cout<<"Order priority queue capacity limit reached."<<endl;
		return false;
	}
	else
	{
		cout<<"Adding purchase order to the queue..."<<endl;
		orderDB[priority * orderDB_width + position] = new order(src_order);
		return true;
	}
}

bool distribution::removeOrder(order& temp_order)
{
    if(orderDB == nullptr)
    {
        cout<<"The order queue is empty."<<endl;
        return false;
    }
	//accesses position by priority formula OR as long as position value does not exceed width of "queue"
    while(orderDB[array_size] == nullptr)
    {
        array_size--; //decrement till hits non-nullptr address, starts at highest "priority"
    }
    if(array_size == -1) //if reached beyond zero, or empty array
    {
        cout<<"The order queue has no orders."<<endl;
        return false;
    }
    else
    {
    	removeProduct(*(orderDB[array_size]->passProduct()));
    	temp_order.copy(*(orderDB[array_size]));
    	delete orderDB[array_size]; //delete pointer at this location array_size
    	orderDB[array_size] = nullptr; //reached non-nullptr element and set to nullptr
   		cout<<"Order has been removed from the priority queue at position ["<<array_size<<"]"<<endl;
    }
    return true;
}

bool distribution::shipOrder()
{
    order temp_order;
    bool check = removeOrder(temp_order);
	if(check == false)
	{
		cout<<"Cannot fulfill a non-existing purchase order..."<<endl;
		return false;
	}
	else
	{
        temp_order.passProduct()->arrivedAt(*distro_location);
		distro_transportation = new transportation(temp_order);
		distro_transportation->shipOut();
	}
	return true;
}

int distribution::findIndex(order& src_order)
{
    int returnIndex = src_order.order::findIndex();
    return returnIndex;
}

int distribution::findIndex2(product& src_product)
{
    int returnIndex = src_product.getCategory();
    return returnIndex;
}


bool distribution::addProduct(product& src_product)
{
	int index = findIndex2(src_product);
	bool check = false;
	if(index == 3)
	{
		cout<<"UNDEFINED CATEGORY... FAILED TO ADD PRODUCT"<<endl;
		return check;
	}

	if(inventory[index] == nullptr) //no existing package LL
	{
		cout<<"Creating new Product at index ["<<index<<"]\n";
		inventory[index] = new package;
		check = inventory[index]->addProduct(src_product);	//addProduct returns bool
		return check;
	}
	else	//add to existing LL
	{
		check = inventory[index]->addProduct(src_product);	//addProduct returns bool
		return check;
	}
}

bool distribution::removeProduct(product& src_product)
{
	int index = findIndex2(src_product);
	bool check = false;
	if(index == 3)
	{
		cout<<"UNDEFINED CATEGORY... FAILED TO REMOVE PRODUCT"<<endl;
		return check;
	}

	if(inventory[index] == nullptr)
	{
		cout<<"This Product Category is Empty."<<endl;
		return check;
	}
	else
	{
		check = (inventory[index]->removeProduct(src_product));	//removeProduct returns bool
		return check;
	}
}

bool distribution::checkAvailable(order& src_order)
{
	int index = findIndex(src_order);
    bool check = false;
	if(index == 3)
	{
		cout<<"UNDEFINED CATEGORY... FAILED TO FIND PRODUCT"<<endl;
		return check;
	}

    product* temp = inventory[index];
	while(src_order.compareName(*temp) == false && temp != nullptr)   //looks for matching product name
	{
		temp = temp->getNext();   //uses product::getNext() to return next ptr
	}
    if(src_order.compareName(*temp) == true) //found matching product names
    {
        check = src_order.compareFull(*temp->getNext());
        return check;
    }
    else //reached end of list without find
    {
        cout<<"Could not find product in inventory."<<endl; 
        return true;
    }
}

void distribution::restock(product& src_product)
{
	int index = findIndex2(src_product);
	if(index == 3)
	{
		cout<<"UNDEFINED CATEGORY... FAILED TO FIND PRODUCT"<<endl;
		return;
	}

	inventory[index]->addProduct(src_product);	  //product::addProduct() returns bool
	return;
}

void distribution::displayInventory()
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"                INVENTORY                "<<endl;
    cout<<"-----------------------------------------"<<endl;
 
	for(int i=0; i<3; i++)	//for loop each element in inventory
    {
        product* current = inventory[i];
        if(current != nullptr)
        {
            while(current->getNext() != nullptr)
            {
                 current->getNext()->displayInfo();
                 current = current->getNext();
            }
        }
        else
        {
            cout<<"Empty Category"<<endl;
        }
       cout<<"-----------------------------------------"<<endl;
	}
	return;
}

void distribution::displayOrders() const
{
    cout<<"-----------------------------------------"<<endl;
    cout<<"             STANDARD ORDERS             "<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=0; i<orderDB_width; i++)
    {
        if(orderDB[i])
        {
            orderDB[i]->displayOrderDetails();
            cout<<endl;
        }
        else
        {
            cout<<"[Empty Slot]"<<endl;
        }
    }
    cout<<"-----------------------------------------"<<endl;
    cout<<"             EXPEDITED ORDERS            "<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=orderDB_width; i<orderDB_width*2; i++)
    {
        if(orderDB[i])
        {
            orderDB[i]->displayOrderDetails();
            cout<<endl;
        }
        else
        {
            cout<<"[Empty Slot]"<<endl;
        }
    }
    cout<<"-----------------------------------------"<<endl;
    cout<<"             OVERNIGHT ORDERS            "<<endl;
    cout<<"-----------------------------------------"<<endl;
    for(int i=orderDB_width*2; i<array_size; i++)
    {
        if(orderDB[i])
        {
            orderDB[i]->displayOrderDetails();
            cout<<endl;
        }
        else
        {
            cout<<"[Empty Slot]"<<endl;
        }
    }
    return;
}

void distribution::loadFromFile(const char* fileName)
{
	ifstream	infile;
	product 	newProduct;
	int 		MAX_CHAR = 100;
	char 		currProductName[MAX_CHAR];
	char 		currCategory[MAX_CHAR];
	char 		currProductID[MAX_CHAR];
	float 		currPrice;
	int 		currQuantity;

	infile.open(fileName);
	if(!infile)
	{
		cerr<<"Failed to open "<<fileName<<"for reading."<<endl;
		exit(1);
	}

	while(!infile.eof())
	{
		infile.get(currProductName, MAX_CHAR, ';');
		infile.get();
		infile.get(currCategory, MAX_CHAR, ';');
		infile.get();
		infile.get(currProductID, MAX_CHAR, ';');
		infile.get();
		infile >> currPrice;
		infile.get();
		infile >> currQuantity;
		infile.ignore(MAX_CHAR, '\r');
		infile.get();

		newProduct.setName(currProductName);
		newProduct.setCategory(currCategory);
		newProduct.setProductID(currProductID);
		newProduct.setPrice(currPrice);
		newProduct.setQuantity(currQuantity);

		addProduct(newProduct);
	}

	infile.close();
}
