#pragma once
#ifndef BAKINGINGREDIENTS_H
#define BAKINGINGREDIENTS_H
#include  <iostream>
#include "PantryItem.h"
using namespace std;

class BakingIngredient : public PantryItem {
public:
	BakingIngredient(string name, string expiration, int quantity) :
		PantryItem(name, expiration, quantity) {}
	void display() override {
		cout << "    + " << name << "\n      - Qty: " << quantity;
		cout << "\n      - Exp: " << expiration << endl;
	}
	string getItem() override {
		return "Baking Ingredient";
	}
};

#endif