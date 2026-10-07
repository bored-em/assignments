#pragma once
#ifndef SNACKS_H
#define SNACKS_H
#include  <iostream>
#include "PantryItem.h"
using namespace std;

class Snacks : public PantryItem {
public:
	Snacks(string name, string expiration, int quantity) :
		PantryItem(name, expiration, quantity) {}
	string getItem() override {
		return "Snacks";
	}
	void display() override {
		cout << "    + " << name << "\n      - Qty: " << quantity;
		cout << "\n      - Exp: " << expiration << endl;
	}
};

#endif