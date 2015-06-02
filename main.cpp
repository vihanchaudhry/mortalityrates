#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"
#include "Country.h"
#include <time.h>
using namespace std;

void parser(BinarySearchTree<Country> *countryList);
void display(Country & anItem);
void menu(BinarySearchTree<Country> *classList);

int main(){

	//Creates a new binarysearchtree
	BinarySearchTree<Country>* countryList = new BinarySearchTree<Country>();

	//Reads the file and populates the class list
	parser(countryList);

	//Displays the menu
	menu(countryList);

	//Deletes the allocated object
	delete countryList;

	//stops the program from terminating
	system("pause");

	return 0;
}

void parser(BinarySearchTree<Country> *countryList){

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
	cout << "Building Binary Search Tree..." << endl;
	clock_t start = clock();
	while(!infile.eof()){
		getline(infile, country, ',');
		getline(infile, year, ',');
		getline(infile, maleData, ',');
		getline(infile, femaleData, ',');
		getline(infile, both);
		
		Country tempCountry(country, atoi(year.c_str()), atoi(maleData.c_str()), atoi(femaleData.c_str()), atoi(both.c_str()));
		countryList->insert(tempCountry);
		i++;
	}
	cout << "Building Finished " << i << " Unique Entries entered." << endl;
	cout << "Time elapsed : " << (double)(clock() - start)/CLOCKS_PER_SEC << " seconds" << endl << endl;
}

void display(Country & anItem)
{
	cout << "Displaying item - " << anItem.getID() << endl;// << " " << anItem.getName() << " " << anItem.getGpa() << endl;
}


void menu(BinarySearchTree<Country> *classList){

	//Variable declaration and intialization
	bool run = true;
	char choice;
	Country smallCountry;
	Country largeCountry;
	Country targetCountry;
	Country foundCountry;
	string country, year;
	clock_t start;
	//Continues to run while the user hasn't designated to quit
	while (run){

		cout << "Enter a choice: ";
		cin >> choice;

		switch (choice){
		case 'B':
			cout << endl << "Breadth First Traversal" << endl << endl;
			classList->breadthFirst(display);
			cout << endl;
			break;

		case 'D':

			cout << endl << "Inorder Traversal" << endl << endl;
			classList->inOrder(display);

			cout << endl << "Preorder Traversal" << endl << endl;
			classList->preOrder(display);

			cout << endl << "Postoreder Traversal" << endl << endl;
			classList->postOrder(display);
			cout << endl;
			break;
		case 'I':
			cout << endl << "Not Coded" << endl << endl;
			break;
		case 'T':

			cout << "Print by Level" << endl << endl;
			classList->print();
			break;

			
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

			targetCountry.setID(country + year);
			start = clock();
			if (classList->getEntry(targetCountry, foundCountry)){
				cout << endl << "Country Found" << endl << endl;
				cout << foundCountry << endl;
				cout << "Time Elapsed: " << (double)(clock() - start) / CLOCKS_PER_SEC << endl << endl;
			}
			else
				cout << endl << "Country not Found" << endl << endl;
			break;
	/*
		case 'R':
			int smallest, largest;

			do{

				do{
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Enter smallest ID: ";
					cin >> smallest;
					if (!cin)
						cout << endl << "Error - Invalid Input" << endl << endl;
				} while (!cin);

				smallStudent.setID(smallest);

				do{
					cin.clear();
					cin.ignore(256, '\n');
					cout << "Enter largest ID: ";
					cin >> largest;
					if (!cin)
						cout << endl << "Error - Invalid Input" << endl << endl;
				} while (!cin);

				largeStudent.setID(largest);
				if (largest < smallest)
					cout << "Error - 'Largest' value must be greater than 'smallest' value";
			} while (largest < smallest);
			cout << endl;

			classList->range(display, smallStudent, largeStudent);

			cout << endl;
			break;
			*/
		case 'A':
			cout << endl << "Hw4 - 22C, Binary Trees" << endl;
			cout << "Developer : Jaison William M. Tiu" << endl;
			cout << "Date : May 26, 2014" << endl << endl;
			break;

		case 'H':
			cout << endl << "HELP" << endl << endl
				<< "B - Tree Breadth-First Traversal: Print by level" << endl
				<< "D - Depth-First Traversals: inorder, preorder, postorder" << endl
				<< "I - Iterative Depth - First Traversals : inorder, preorder, postorder" << endl
				<< "T - Print tree as an indented list" << endl
				<< "S - Search by a unique key" << endl
				<< "R - Print the items within a given range in the tree." << endl
				<< "H - Help - to show the menu" << endl
				<< "Q - Quit. " << endl << endl;

			break;

		case 'Q':
			run = false;
			break;

			//Input validation if anything other than the choices is chosen then the user is prompted again
		default:
			cout << endl << "Invalid input" << endl << endl;

			break;

		}

	}


}
