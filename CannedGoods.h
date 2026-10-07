#pragma once
#ifndef CANNEDGOODS_H
#define CANNEDGOODS_H
#include  <iostream>
#include "PantryItem.h"
using namespace std;

class CannedGoods : public PantryItem {
public:
	CannedGoods(string name, string expiration, int quantity) :
		PantryItem(name, expiration, quantity) {}
	string getItem() override {
		return "Canned Good";
	}
	void display() override {
		cout << "    + " << name << "\n      - Qty: " << quantity;
		cout << "\n      - Exp: " << expiration << endl;
	}
};

#endif