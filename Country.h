// Specification and implementation file for the Country class
/*
	Description:
		The country class holds the data for each country read from the input file.
		This allows for all the information for an indiviual country to be consolidated
		in a single object rather than having multiple data members in a tree's binary node
		or hashtable slot.

	Added by: Jaison Tiu
*/
#ifndef COUNTRY_H
#define COUNTRY_H
#include <string>
#include <iostream>
using namespace std;

class Country
{
private:
	string compare;
	string id;
	string name;
	int year;
	int maleMortality;
	int femaleMortality;
	int combinedMortality;

public:
	Country(){ id = ""; name = ""; maleMortality = 0; femaleMortality = 0; combinedMortality = 0; };
	Country(string compareCode){ compare = compareCode; };
	Country(string countryName, int countryYear, int maleNumber, int femaleNumber, int combinedNumber){ name = countryName; year = countryYear; id = countryName + to_string(countryYear); maleMortality = maleNumber; femaleMortality = femaleNumber; combinedMortality = combinedNumber; };
	~Country(){};

	void setCompare(string compareCode) { compare = compareCode; };
	string getCompare() const { return compare; };

	void setName(string countryName) { name = countryName; };
	string getName() const { return name; };

	void setYear(int countryYear){ year = countryYear; };
	int getYear()const{ return year; };

	void setID(string countryID){ id = countryID; };
	string getID() const { return id; };

	void setMaleMortality(int maleNumber){ maleMortality = maleNumber; };
	int getMaleMortality()const { return maleMortality; };

	void setFemaleMortality(int femaleNumber){ femaleMortality = femaleNumber; };
	int getFemaleMortality() const { return femaleMortality; };

	void setCombinedMortality(int combinedNumber){ combinedMortality = combinedNumber; };
	int getCombinedMortality()const { return combinedMortality; };

	// Overloaded operators
	friend bool operator<= (Country country, Country otherCountry);
	friend bool operator>=(Country country, Country otherCountry);
	friend bool operator< (Country country, Country otherCountry);
	friend bool operator==(Country country, Country otherCountry);
	friend bool operator>(Country country, Country otherCountry);
	friend ostream& operator<<(ostream& os, const Country& student);
};

bool operator<= (Country country, Country otherCountry){
	if (otherCountry.getCompare() == "ID"){
		return country.getID() <= otherCountry.getID();
	}
	return country.getName() <= otherCountry.getName();
};

bool operator>=(Country country, Country otherCountry){
	if (otherCountry.getCompare() == "ID"){
		return country.getID() >= otherCountry.getID();
	}
	return country.getName() >= otherCountry.getName();
};

bool operator< (Country country, Country otherCountry){
	if (otherCountry.getCompare() == "ID"){
		return country.getID() < otherCountry.getID();
	}
	return country.getName() < otherCountry.getName();
};

bool operator==(Country country, Country otherCountry){

	if (otherCountry.getCompare() == "ID"){
		return country.getID() == otherCountry.getID();
	}
	return country.getName() == otherCountry.getName();
	};

bool operator>(Country country, Country otherCountry){ 
	if (otherCountry.getCompare() == "ID"){
		return country.getID() > otherCountry.getID();
	}
	return country.getName() > otherCountry.getName();
};

/*******************************************
* Allows the country object to be directly *
* used by output streams.				   *
********************************************/
ostream& operator<<(ostream& os, const Country& country)
{
	os << "Country Name: " << country.getName() << endl
	   << "Country Year: " << country.getYear() << endl
	   << "Male Mortality per Thousand: " << country.getMaleMortality() << endl
	   << "Female Mortality per Thousand: " << country.getFemaleMortality() << endl
	   << "Male and Female Mortality per Thousand: " << country.getCombinedMortality() << endl;
	return os;
}
#endif
