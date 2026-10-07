#pragma once
#ifndef GRAINPASTA_H
#define GRAINPASTA_H
#include  <iostream>
#include "PantryItem.h"
using namespace std;

class GrainPasta : public PantryItem {
public: 
	GrainPasta(string name, string expiration, int quantity) :
		PantryItem(name, expiration, quantity){}
	void display() override {
		cout << "    + " << name << "\n      - Exp: " << expiration;
		cout << "\n      - Qty: " << quantity << endl;
	}
	string getItem() override {
		return "Grain/Pasta";
	}
};

#endif