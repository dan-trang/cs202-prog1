/***********************************************
Daniel Trang
Jan.16.2021
CS202: Programming Systems
Program #1: Distribution Solution
Main.cpp

To simplify this project scope, I've defined functions
to act as the Manufacturing Company (productMake) and
front-end data processing which receives customer info
(getFinalDestination). The bulk of the functions are
mainly for UI display and allow the user to interact with
the five options: add new order, display inventory, display
orders, fulfill an order shipment, and exit the program.

I've included a product menu that will show a catalog of
all the different products the user can select for purchase.
None of the functions can be structurally modified from main,
but the products data file and type of distribution center can
be changed for testing.
************************************************/
#include "location.h"
#include "product.h"
#include "order.h"
//#include "transportation.h"
#include "distribution.h"
using namespace std;

char userMenu();
char productMenu();
void execute(distribution& nationalWarehouse, char userInput);
bool continueMenu();
void productMake(char product_choice, int quantity, product& purchaseProduct);
void getFinalDestination(location& userLocation);
void makeOrder(char* customer_name, int selected_shipping, product& purchaseProduct, location& userLocation, order& purchaseOrder);

int main()
{
	bool check = true;
	char userInput;
	char scale[9] = "national"; 	//play around with "national" vs. "local"
	distribution nationalWarehouse(scale);  //distro object
	char datafile[] = "products.txt"; //file to read from
	nationalWarehouse.loadFromFile(datafile); //adds products from .txt file to distro obj

	userInput = userMenu();
	while(userInput != '5' && check == true)
	{
		execute(nationalWarehouse, userInput);
		check = continueMenu();
		if(check == true)
		{
			userInput = userMenu();
		}
	}

	cout<<"*** PROGRAM EXIT ***"<<endl;
	return 0;
}

//Main Menu
char userMenu()
{
	char userInput;

	cout<<"----------------- CS202 DISTRIBUTION PROGRAM -----------------"<<endl;
	cout<<"  Welcome, [user]. Please read the following options below."<<endl;
	cout<<"--------------------------------------------------------------"<<endl;
	cout<<"1. Add a new purchase order"<<endl;	//adds new order to order list
	cout<<"2. Display all inventory in the system"<<endl;	//display inventory 
    cout<<"3. Display all purchase orders in the system"<<endl; //display all customer orders
	cout<<"4. Simulate order fulfillment and shipping (one order)"<<endl; //will fulfill all orders
	cout<<"5. Exit Program\n"<<endl;

	cout<<"Please enter the number of the option you wish to select: ";
	cin>>userInput;
	return userInput;
}

//Product Catalog
char productMenu()
{
	char userSelection, toPurchase = '0', percent = '%';

	cout<<"----------------- PRODUCT CATALOG -----------------"<<endl;
	cout<<" 50"<<percent<<" OFF all purchases above $2000!! Holiday Sales "<<endl;
	cout<<" end soon... our products are limited. Buy Now!!   "<<endl;
	cout<<"---------------------------------------------------\n"<<endl;
	cout<<"1. CPUs"<<"\t"<<"2. GPUs"<<"\t"<<"3. Motherboards\n"<<endl;
    cout<<"Select a category (1, 2, 3): ";
    cin>>userSelection;

	if(userSelection == '1')
	{
		cout<<"1. AMD RYZEN 5 3600X | $199.99"<<endl;
		cout<<"2. AMD RYZEN 7 3800X | $399.99"<<endl;
		cout<<"3. AMD RYZEN 9 3950X | $723.99"<<endl;

		cin>>toPurchase;
		return toPurchase;
	}
	else if(userSelection == '2')
	{
		cout<<"4. EVGA GeForce GTX 1080TI | $1149.00"<<endl;
		cout<<"5. NVIDIA GeForce RTX 2080TI | $1499.99"<<endl;
		cout<<"6. NVIDIA RTX 3090 Founder's Edition | $1799.00"<<endl;

		cin>>toPurchase;
		return toPurchase;
	}
	else if(userSelection == '3')
	{
		cout<<"7. ASUS Prime X570-P | $149.99"<<endl;
		cout<<"8. ASUS RoG Strix X570-E | $447.90"<<endl;
		cout<<"9. ASUS RoG X570 Crosshair VIII Formula | $583.99"<<endl;

		cin>>toPurchase;
		return toPurchase;
	}
    return toPurchase;
}

//checks if user would like to continue
bool continueMenu()
{
	char yesNo;

	cout<<"Would you like to return to the Options Menu? (y/n): ";
	cin>>yesNo;

	if(yesNo == 'y' || yesNo == 'Y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//"Manufactures" the item to be transported
void productMake(char product_choice, int quantity, product& purchaseProduct)
{
	int MAX_CHAR = 100;
	float price;
	char product_name[MAX_CHAR], category[MAX_CHAR], product_ID[MAX_CHAR];

    if(product_choice == '1')
    {
        strcpy(product_name, "AMD Ryzen 5 3600X");
        strcpy(category, "CPU");
        strcpy(product_ID,"795001");
        price = 199.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }

    if(product_choice == '2')
    {
        strcpy(product_name, "AMD Ryzen 7 3800X");
        strcpy(category, "CPU");
        strcpy(product_ID,"950372");
        price = 399.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '3')
    {
        strcpy(product_name, "AMD Ryzen 9 3950X");
        strcpy(category, "CPU");
        strcpy(product_ID,"842509");
        price = 723.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '4')
    {
        strcpy(product_name, "NVIDIA GeForce GTX 1080TI");
        strcpy(category, "GPU");
        strcpy(product_ID,"907247");
        price = 1149.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '5')
    {
        strcpy(product_name, "NVIDIA GeForce RTX 2080TI");
        strcpy(category, "GPU");
        strcpy(product_ID,"927049");
        price = 1499.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '6')
    {
        strcpy(product_name, "NVIDIA RTX 3090 Founder's Edition");
        strcpy(category, "GPU");
        strcpy(product_ID,"225086");
        price = 1799.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '7')
    {
        strcpy(product_name, "ASUS Prime X570-P");
        strcpy(category, "Motherboard");
        strcpy(product_ID,"605982");
        price = 149.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }

    if(product_choice == '8')
    {
        strcpy(product_name, "ASUS RoG Strix X570-E");
        strcpy(category, "Motherboard");
        strcpy(product_ID,"623489");
        price = 447.90;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
    if(product_choice == '9')
    {
        strcpy(product_name, "ASUS RoG X570 Crosshair VIII Formula");
        strcpy(category, "Motherboard");
        strcpy(product_ID,"652471");
        price = 583.99;
        product toCopyFrom(product_name, category, product_ID, price, quantity);
        purchaseProduct.copy(toCopyFrom);
        return;
    }
        
	cout<<"Invalid Product"<<endl;
    return;
}

//constructs the Customer's shipping location
void getFinalDestination(location& userLocation)
{
	int zip, MAX_CHAR = 100;
	char location_name[MAX_CHAR] = "CUSTOMER", street[MAX_CHAR], state[MAX_CHAR];

	cout<<"Fill out the shipping address...\n"<<endl;
	cout<<"Street (ex. 1234 Sesame St, Manhattan): ";
    cin.ignore(MAX_CHAR, '\n');
	cin.get(street, MAX_CHAR);
	cout<<"State (ex. Oregon, OR, OREGON): ";
    cin.ignore(MAX_CHAR, '\n');
	cin.get(state, MAX_CHAR);
	cout<<"Zip Code (ex. 97045): ";
	cin >> zip;

	location toCopyFrom(location_name, street, state, zip);
    userLocation.copy(toCopyFrom);
	return;
}

//Builds the purchase order
void makeOrder(char* customer_name, int selected_shipping, product& purchaseProduct, location& userLocation, order& purchaseOrder)
{
    order toCopyFrom(customer_name, selected_shipping, purchaseProduct, userLocation);
    purchaseOrder.copy(toCopyFrom);
    return;
}


//User Selected option all performed in here
void execute(distribution& nationalWarehouse, char userInput)
{
	int selected_shipping, quantity, MAX_CHAR = 100;
	char customer_name[MAX_CHAR];
	char product_choice;
	location userLocation;
	product purchaseProduct;
    order purchaseOrder;

	switch(userInput)
	{
		//Adds new purchase order
		case '1':
			//ask user for name, shipping destination, shipping type, product choice, and quantity
			product_choice = productMenu();

			cout<<"How many do you want to buy?: "<<endl;
			cin>>quantity;

			productMake(product_choice, quantity, purchaseProduct);

			cout<<"Enter your name or business name: ";
            cin.ignore(MAX_CHAR, '\n');
			cin.get(customer_name, MAX_CHAR);

			getFinalDestination(userLocation);

			cout<<"Selection shipping (1. standard, 2. expedited, 3. overnight): ";
            cin.ignore(MAX_CHAR, '\n');
			cin>>selected_shipping;

			cout<<"Creating your purchase order... ";
            makeOrder(customer_name, selected_shipping, purchaseProduct, userLocation, purchaseOrder);
			nationalWarehouse.addOrder(purchaseOrder);  //saves order to distro center
			cout<<"Order Entry has been saved!"<<endl;
			break;

		//Display all inventory
		case '2':
            nationalWarehouse.displayInventory();
			break;

		//Display all purchase orders in the system
		case '3':
            nationalWarehouse.displayOrders();
			break;

		//Runs the order fulfillment and shipping simulation once
		case '4':
			cout<<"Shipping out orders"<<endl;
            nationalWarehouse.shipOrder();
			cout<<"All orders have been fulfilled"<<endl;
			break;

        //Exits the program
        case '5':
            cout<<"Exiting Program..."<<endl;
            break;

		default:
			cout<<"Invalid Input."<<endl;
			break;
	}
}

