#pragma once
#ifndef SPICES_H
#define SPICES_H
#include <iostream>
#include "PantryItem.h"
using namespace std;

class Spices : public PantryItem {
public:
	Spices(string name, string expiration, int quantity) :
		PantryItem(name, expiration, quantity) {}
	string getItem() override {
		return "Spice";
	}
	void display() override {
		cout << "    + " << name << "\n      - Qty: " << quantity;
		cout << "\n      - Exp: " << expiration << endl;
	}
};

#endif

