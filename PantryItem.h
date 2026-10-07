#pragma once
#ifndef PANTRYITEM_H
#define PANTRYITEM_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class PantryItem {
protected:
	string name;
	string expiration;
	int quantity;
public:
	PantryItem(string name, string expiration, int quantity) : 
		name(name), expiration(expiration), quantity(quantity) {}
	string getName() { return name; }
	string getExpiration() { return expiration; }
	int getQuantity() { return quantity; }
	virtual string getItem() = 0;
	virtual void display() = 0;
};

#endif