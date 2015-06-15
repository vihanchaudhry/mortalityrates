/**
CIS 22C Group Project - Spring 2015
Project: Mortality Rates
Group #1
Developers: Jason Liang, Jaison Tiu, Vihan Chaudhry, Victor La
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include "Country.h"
#include "HashTable.h"
#include <time.h>
using namespace std;

// Function Prototypes
void parser(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList, HashTable<Country> *hashTable);
void display(Country & anItem);
void mainCommandManager(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList,HashTable<Country> *hashTable);
void removeStuffGlobal(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList, HashTable<Country> *hashTable);
char secondaryBSTCommandManager(BinarySearchTree<Country *> *secondaryList); 
void introduceProgram();
void displayMainMenu();
void displayHashTableMenu();
char hashTableCommandManager(HashTable<Country> *hashTable);
char uniqueBSTCommandManager(BinarySearchTree<Country *> *uniqueList);
void displayBSTMenu(bool unique);
void searchHashTable(HashTable<Country> *hashTable);
void displayHashTableList(HashTable<Country> *hashTable);
void printHashTable(HashTable<Country> *hashTable);
void printHashTableStatistics(HashTable<Country> * hashTable);

int main()
{
	BinarySearchTree<Country *>* uniqueList = new BinarySearchTree<Country *>("ID"); // Create BST
    BinarySearchTree<Country *>* secondaryList = new BinarySearchTree<Country *>("Country"); // Create BST
    HashTable<Country>* hashTable = new HashTable<Country>(); // Create Hash Table
    
	parser(uniqueList, secondaryList, hashTable); // Read file and populate data structures.
    introduceProgram();
    
	mainCommandManager(uniqueList, secondaryList, hashTable); // Read commands and execute.

	delete uniqueList;
    delete secondaryList;
    delete hashTable;

	system("pause"); //stops the program from terminating
	return 0;
}

void parser(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList, HashTable<Country> *hashTable){

	ifstream infile("data.csv");
	if (infile.fail()){
		cout << "File not found";
		return;
	}
	int i = 0;
	string country;
	string year;
	string maleData;
	string femaleData;
	string both;
    Country *countryPtr;
	cout << "Building Binary Search Tree..." << endl;
	clock_t start = clock();
	while(!infile.eof()){
	//while (i<25){
		getline(infile, country, ',');
		getline(infile, year, ',');
		getline(infile, maleData, ',');
		getline(infile, femaleData, ',');
		getline(infile, both);
		
		countryPtr = new Country(country, atoi(year.c_str()), atoi(maleData.c_str()), atoi(femaleData.c_str()), atoi(both.c_str()));
        //Inserting into BST
		uniqueList->insert(countryPtr);
        
        //Inserting into second BST
		secondaryList->insert(countryPtr);
        //Inserting into hash table
        
        hashTable->insert(countryPtr);
		i++;
	}
	cout << "Building Finished " << i << " Unique Entries entered." << endl;
	cout << "Time elapsed : " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void display(Country * anItem)
{
	cout << "Displaying item - " << anItem->getID() << endl;// << " " << anItem.getName() << " " << anItem.getGpa() << endl;
}

void mainCommandManager(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList, HashTable<Country> *hashTable)
{
	//Variable declaration and intialization
	bool run = true;
	char choice = '/0';
    
    while (run)
    {
		if (choice == 'u' || choice == 's' || choice == 'h'){
			removeStuffGlobal(uniqueList, secondaryList, hashTable);
		}
		else{
			displayMainMenu();
			cout << "Enter a choice: ";
			cin >> choice;
		}
        switch (choice)
        {
                case 'H':
                case 'h':
                        choice = hashTableCommandManager(hashTable);
                        break;
                case 'U':
                case 'u':
                        choice = uniqueBSTCommandManager(uniqueList);
                        //displayMainMenu();
                    break;
                case 'S':
                case 's':
                        choice = secondaryBSTCommandManager(secondaryList);
                        //displayMainMenu();
                    break;
				case'R':
				case'r':
					break;
                case 'Q':
                case 'q':
                    run = false;
                    break;
        }
    }
}

/*~~~~~~~~~~~
 Introduction of the program to the user.
*/
void introduceProgram()
{
	cout << "Hello! Welcome to Mortality Rates!\n"
         << "Did you know that there are 196 countries in world?\n"
         << "This program was developed by Jason Liang, Jaison Tiu, Vihan \n"
		 << "Chaudhry and Victor La.\n"
         << "It utilizes two Binary Search Trees and a Hash Table\n"
         << "to organize the mortality data of the countries of the world!\n\n";
}

/*~~~~~~~~~~~~
 Display the main menu.
 */
void displayMainMenu()
{
	cout << "\t\t _________________________________________" << endl
		 << "\t\t|                 MAIN MENU               |" << endl
		 << "\t\t| H : Hash Table Menu                     |" << endl
		 << "\t\t| U : Binary Search Tree by Unique Key    |" << endl
		 << "\t\t| S : Binary Search Tree by Secondary Key |" << endl
		 << "\t\t| Q : Quit                                |" << endl
		 << "\t\t|_________________________________________|" << endl << endl;
}

/*~~~~~~~~~~~~
 Display the Hash Table's menu.
*/
void displayHashTableMenu()
{
	cout << "\t\t ______________________________________" << endl
 		 << "\t\t|           HASH TABLE MENU            |" << endl
		 << "\t\t| S : Search by Unique Key             |" << endl
		 << "\t\t| D : Display Hash Table as a List     |" << endl
		 << "\t\t| P : Print the Indented Hash Table    |" << endl
		 << "\t\t| T : Show Hash Table Statistics       |" << endl
		 << "\t\t| H : Help (Show Menu)                 |" << endl
		 << "\t\t| B : Back                             |" << endl
	 	 << "\t\t|_____________________________________ |" << endl << endl;
}

/*~~~~~~~~~~~~
 Manage the hash table menu.
*/
char hashTableCommandManager(HashTable<Country> *hashTable)
{
    bool run = true;
    char choice;
    
    displayHashTableMenu();
    
    while (run)
    {
        cout << "Enter a choice: ";
        cin >> choice;
        
        switch(choice)
        {
            case 'S':
            case 's':
                searchHashTable(hashTable);
                break;
            case 'D':
            case 'd':
                displayHashTableList(hashTable);
                break;
            case 'P':
            case 'p':
                printHashTable(hashTable);
                break;
            case 'T':
            case 't':
                printHashTableStatistics(hashTable);
                break;
            case 'H':
            case 'h':
                displayHashTableMenu();
                break;
			case 'R':
			case 'r':
				return 'h';
				break;
            case 'B':
            case 'b':
                run = false;
                break;
        }
    }
	return '/0';
}


/*~~~~~~~~~~~~
 Display the BST's menu.
*/
void displayBSTMenu(bool unique)
{
    if (unique)
        cout << "\n======BST (Unique Key) Menu======\n";
    else
        cout << "\n======BST (Secondary Key) Menu======\n";
	cout << "\t\t ______________________________________" << endl
		 << "\t\t|              MAIN MENU               |" << endl
		 << "\t\t| I : In-order Traversal               |" << endl
		 << "\t\t| E : Pre-order Traversal              |" << endl
		 << "\t\t| O : Post-order Traversal             |" << endl
		 << "\t\t| U : Breadth-first Traversal          |" << endl
		 << "\t\t| T : Print by Level                   |" << endl
		 << "\t\t| R : Print by Range                   |" << endl
		 << "\t\t| S : Search                           |" << endl
		 << "\t\t| H : Help (Show Menu)                 |" << endl
		 << "\t\t| B : Back                             |" << endl
		 << "\t\t|_____________________________________ |" << endl << endl;
}

/*~~~~~~~~~~~~
 Manage the BST by unique key menu.
*/
char uniqueBSTCommandManager(BinarySearchTree<Country *> *uniqueList)
{
    bool run = true;
    char choice;
	string code = "ID";
    Country *smallCountry = new Country(code);
    Country *largeCountry = new Country(code);
	Country *targetCountry = new Country(code);
	Country *foundCountry = new Country(code);
    string country, year;
    clock_t start;
    
    displayBSTMenu(true);
    
	while (run)
	{
		cout << "Enter a choice: ";
		cin >> choice;

		switch (choice)
		{
		case 'i':
		case 'I':
			cout << endl << "In-order Traversal" << endl << endl;
			uniqueList->inOrder(display);
			break;
		case 'e':
		case 'E':
			cout << endl << "Pre-order Traversal" << endl << endl;
			uniqueList->preOrder(display);
			break;
		case 'o':
		case 'O':
			cout << endl << "Post-order Traversal" << endl << endl;
			uniqueList->postOrder(display);
			cout << endl;
			break;
		case 'u':
		case 'U':
			cout << endl << "Breadth-first Traversal" << endl << endl;
			uniqueList->breadthFirst(display);
			cout << endl;
		case 't':
		case 'T':
			cout << "Print by Level" << endl << endl;
			uniqueList->print();
			break;
		case 's':
        case 'S':
			do{
				cin.clear();
                cin.ignore(256, '\n');
                cout << "Enter the name of the country you want to find: ";
                getline(cin, country);
                cout << "Enter the year of the country you want to find: ";
                cin >> year;
                if (!cin)
                    cout << endl << "Error - Invalid Input" << endl << endl;
            } while (!cin);
                    
            targetCountry->setID(country + year);
            start = clock();
			if(uniqueList->getEntry(targetCountry, foundCountry, display)){
                cout << endl << "Country Found" << endl << endl;
                cout << "Time Elapsed: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl << endl;
            }
            else
                cout << endl << "Country not Found" << endl << endl;
            break;
		case 'R':
		case 'r':
			do{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter Lower bound Country Name: ";
				getline(cin, country);
				cout << "Enter the year of the lower bound country: ";
				cin >> year;
				if (!cin)
					cout << endl << "Error - Invalid Input" << endl << endl;
			} while (!cin);

			smallCountry->setID(country + year);
			do{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter Upper bound Country Name: ";
				getline(cin, country);
				cout << "Enter the year of the uppper bound country: ";
				cin >> year;

				if (!cin)
					cout << endl << "Error - Invalid Input" << endl << endl;
			} while (!cin);

			largeCountry->setID(country + year);
			cout << endl;
			uniqueList->range(display, smallCountry, largeCountry);
			cout << endl;
			break;
		case 'h':
		case 'H':
			displayBSTMenu(true);
			break;
		case 'b':
		case 'B':
			run = false;
			break;

		//Input validation if anything other than the choices is chosen then the user is prompted again
		default:
			cout << endl << "Invalid input" << endl << endl;
			break;
		}
	}
	return '/0';
}

/*~~~~~~~~~~~~
 Manage the BST by secondary key menu.
*/
char secondaryBSTCommandManager(BinarySearchTree<Country *> *secondaryList)
{
	bool run = true;
	char choice;
	string code = "Country";
	Country *smallCountry = new Country(code);
	Country *largeCountry = new Country(code);
	Country *targetCountry = new Country(code);
	Country *foundCountry = new Country(code); 
	string country, year;
	clock_t start;

	displayBSTMenu(false);

	while (run)
	{
		cout << "Enter a choice: ";
		cin >> choice;

		switch (choice)
		{
		case 'i':
		case 'I':
			cout << endl << "In-order Traversal" << endl << endl;
			secondaryList->inOrder(display);
			break;
		case 'e':
		case 'E':
			cout << endl << "Pre-order Traversal" << endl << endl;
			secondaryList->preOrder(display);
			break;
		case 'o':
		case 'O':
			cout << endl << "Post-order Traversal" << endl << endl;
			secondaryList->postOrder(display);
			cout << endl;
			break;
		case 'u':
		case 'U':
			cout << endl << "Breadth-first Traversal" << endl << endl;
			secondaryList->breadthFirst(display);
			cout << endl;
		case 't':
		case 'T':
			cout << "Print by Level" << endl << endl;
			secondaryList->print();
			break;
		case 's':
		case 'S':
			do{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter the name of the country you want to find: ";
				getline(cin, country);
				if (!cin)
					cout << endl << "Error - Invalid Input" << endl << endl;
			} while (!cin);

			targetCountry->setName(country);
			start = clock();
			if (secondaryList->getEntry(targetCountry, foundCountry, display)){
				cout << endl << "Country Found" << endl << endl;
				cout << "Time Elapsed: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl << endl;
			}
			else
				cout << endl << "Country not Found" << endl << endl;
			break;
		case 'r':
		case 'R':
			do{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter Lower bound Country Name: ";
				getline(cin, country);
				cout << "Enter the year of the lower bound country: ";
				cin >> year;

				if (!cin)
					cout << endl << "Error - Invalid Input" << endl << endl;
			} while (!cin);

			smallCountry->setName(country);
			do{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Enter Upper bound Country Name: ";
				getline(cin, country);
				cout << "Enter the year of the uppper bound country: ";
				cin >> year;
				if (!cin)
					cout << endl << "Error - Invalid Input" << endl << endl;
			} while (!cin);

			largeCountry->setName(country);
			cout << endl;
			secondaryList->range(display, smallCountry, largeCountry);
			break;
		case 'h':
		case 'H':
			displayBSTMenu(false);
			break;
		case 'b':
		case 'B':
			run = false;
			break;
		//Input validation if anything other than the choices is chosen then the user is prompted again
		default:
			cout << endl << "Invalid input" << endl << endl;
			break;
		}
	}
	return '/0';
}

void removeStuffGlobal(BinarySearchTree<Country *> *uniqueList, BinarySearchTree<Country *> *secondaryList, HashTable<Country> *hashTable){
	string country;
	string year;
	string id;
	time_t start;
	Country *removeCountryID = new Country("ID");
	Country *removeCountryName = new Country("Country");

	do
	{
		cin.clear();
		cin.ignore(256, '\n');
		cout << "Enter the name of the country you want to delete: ";
		getline(cin, country);
		cout << "Enter the year of the country you want to delete: ";
		cin >> year;
		if (!cin)
			cout << endl << "Error - Invalid Input" << endl << endl;
	} while (!cin);
	id = country + year;
	removeCountryID->setID(id);
	removeCountryName->setID(id);
	start = clock();
	if (uniqueList->remove(removeCountryID)){
		secondaryList->remove(removeCountryName);
		hashTable->deleteItem(id);
		cout << endl << "Country Deleted" << endl << endl;
		cout << "Time Elapsed: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl << endl;
	}
	else
		cout << endl << "Country not Found" << endl << endl;
}

/*~~~~~~~~~~~
 Search Manager manages the search option.
*/
void searchHashTable(HashTable<Country> *hashTable)
{
    string country;
    string year;
    do{
        cin.clear();
        cin.ignore(256, '\n');
        cout << "Enter the name of the country you want to find: ";
        getline(cin, country);
        cout << "Enter the year of the country you want to find: ";
        cin >> year;
        if (!cin)
            cout << endl << "Error - Invalid Input" << endl << endl;
    } while (!cin);

    string ID = country + year;
    clock_t start = clock();
    Country *countryPtr = hashTable->search(ID);
    
    if (countryPtr == NULL)
    {
        cout << ID << " was not found.\n";
    }
    else
    {
        cout << "Country: " << countryPtr->getName() << endl
             << "Year: " << countryPtr->getYear() << endl
             << "Male mortality: " << countryPtr->getMaleMortality() << endl
             << "Female mortality: " << countryPtr->getFemaleMortality() << endl
             << "Combined mortality: " << countryPtr->getCombinedMortality() << endl << endl;
    }
    cout << "Time elapsed : " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << endl << endl;
}

/*~~~~~~~~~~~~~
 Display the hash table. (just the first elements if set).
 */
void displayHashTableList(HashTable<Country> *hashTable)
{
    cout << "\nHere are the items in the hash table:\n";
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (hashTable->getTable()[i].size() > 0)
        {
            cout << hashTable->getTable()[i][0]->getName() << endl;
        }
    }
}


/*~~~~~~~~~~~~~
 Display the entire Hash table and it's collisions or if elements are not set.
 */
void printHashTable(HashTable<Country> *hashTable)
{
    cout << "\nPrinting the Hash Table:\n\n";
    
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        cout << "\nIndex " << i << ": ";
        
        if (hashTable->getTable()[i].size() == 0)
        {
            cout << "//empty\n";
        }
        else
        {
            cout << hashTable->getTable()[i][0]->getName() << endl;
            
            for (int j = 1; j < hashTable->getTable()[i].size(); j++)
            {
                cout << "\t\t\t" << hashTable->getTable()[i][j]->getName() << endl;
            }
        }
    }
}

/*~~~~~~~~~~~~~~
 Print statistics: number of collisions, load factor, number of full buckets, number of empty buckets,
 average number of nodes stored at index 1 or 2.
 */
void printHashTableStatistics(HashTable<Country> *hashTable)
{
    cout << "\nStatistics:\n"
    << "\tLoad factor: " << fixed << setprecision(2) << hashTable->getLoadFactor()*100 << "%" << endl
    << "\tNumber of full buckets: " << hashTable->getFullBuckets() << endl
    << "\tAverage number of nodes in buckets: " << hashTable->getAverageNodesInBucket() << endl
    << "\tCollision count: " << hashTable->getCollisionCount() << endl
    << "\tOverflow count: " << hashTable->getOverflowCount() << endl << endl;
}
