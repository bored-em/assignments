#include <iostream>
#include <vector>
#include <string> 
#include "GrainPasta.h"
#include "Spices.h"
#include "BakingIngredients.h"
#include "Snacks.h"
#include "CannedGoods.h"
using namespace std;

void display(const vector<PantryItem*>& category, const string& categoryName) {
	if (category.empty()) {
		cout << "No items found in " << categoryName << endl;
		return;
	}
	cout << categoryName << ":" << endl;
	for (const auto& item : category) {
		item->display();
	}
}

void addItem(vector<PantryItem*>& grainPasta, vector<PantryItem*>& spices, vector<PantryItem*>& bakingIngredients, vector<PantryItem*>& snacks, vector<PantryItem*>& cannedGoods) {
	int choice;
	int quantity;
	string name;
	string expiration;

	cout << "Choose the Category of the Item:" << endl;
	cout << "1. Grain/Pasta \n2. Spices \n3. Baking Ingredients \n4. Canned Goods \n5. Snacks \nCHOICE: ";
	cin >> choice;

	cout << "Enter Name of Item: ";
	cin >> name;
	cout << "Enter Expiration Date (MM-DD-YYYY): ";
	cin >> expiration;
	cout << "Enter Quantity of Item: ";
	cin >> quantity;

	PantryItem* item = nullptr;
	switch (choice) {
	case 1:
		item = new GrainPasta(name, expiration, quantity);
		grainPasta.push_back(item);
		break;
	case 2:
		item = new Spices(name, expiration, quantity);
		spices.push_back(item);
		break;
	case 3:
		item = new BakingIngredient(name, expiration, quantity);
		bakingIngredients.push_back(item);
		break;
	case 4:
		item = new Snacks(name, expiration, quantity);
		snacks.push_back(item);
		break;
	case 5:
		item = new CannedGoods(name, expiration, quantity);
		cannedGoods.push_back(item);
		break;
	default:
		cout << "ERROR: Choose a valid input." << endl;
		delete item;
		return;
	}
}

void removeItem(vector<PantryItem*>& category) {
	if (category.empty()) {
		cout << "No items found in this category." << endl;
		return;
	}
	string item;
	cout << "Name of the item you would like to remove: ";
	cin >> item;
	int index = -1;
	for (int i = 0; i < category.size(); i++) {
		if (category[i]->getName() == item) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		delete category[index];
		category.erase(category.begin() + index);
		cout << "Item was removed from category." << endl;
	}
	else {
		cout << "ERROR: Item not found" << endl;
	}
}

int main() {
	vector<PantryItem*> grainPasta;
	vector<PantryItem*> spices;
	vector<PantryItem*> bakingIngredients;
	vector<PantryItem*> snacks;
	vector<PantryItem*> cannedGoods;
	cout << "======================================   ^---^  " << endl;
	cout << "WELCOME TO THE HOME PANTRY ORGANIZER!!  (O v O) " << endl;
	cout << "====================================== ((_____))" << endl;
	cout << "                                          ^ ^" << endl;
	int choice;
	while (true) {
		cout << "1. Display Entire Pantry \n2. Display Specific Category \n3. Add Item \n4. Remove Item \n5. Exit Program" << endl;
		cout << "Enter Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			display(grainPasta, "Grains/Pastas");
			display(spices, "Spices");
			display(bakingIngredients, "Baking Ingredients");
			display(snacks, "Snacks");
			display(cannedGoods, "Canned Goods");
			break;
		case 2: {
			cout << "Choose a category you would like to display" << endl;
			cout << "1. Grain/Pasta \n2. Spices \n3. Baking Ingredients \n4. Snacks \n5. Canned Goods" << endl;
			cout << "Enter Choice: ";
			int pick;
			cin >> pick;
			switch (pick) {
			case 1:
				display(grainPasta, "Grains/Pastas");
				break;
			case 2:
				display(spices, "Spices");
				break;
			case 3:
				display(bakingIngredients, "Baking Ingredients");
				break;
			case 4:
				display(snacks, "Snacks");
				break;
			case 5:
				display(cannedGoods, "Canned Goods");
				break;
			default:
				cout << "ERROR:Choose a valid input." << endl;
			}
			break;
		}

		case 3:
			addItem(grainPasta, spices, bakingIngredients, snacks, cannedGoods);
			break;
		case 4: {
			  cout << "Choose category of item you want to remove" << endl;
			  cout << "1. Grain/Pasta \n2. Spices \n3. Baking Ingredients \n4. Snacks \n5. Canned Goods" << endl;
			  cout << "Enter Choice: ";
			  int pick;
			  cin >> pick;
			  switch (pick) {
			  case 1:
				  removeItem(grainPasta);
				  break;
			  case 2:
				  removeItem(spices);
				  break;
			  case 3:
				  removeItem(bakingIngredients);
				  break;
			  case 4:
				  removeItem(snacks);
				  break;
			  case 5:
				  removeItem(cannedGoods);
				  break;
			  default:
				  cout << "ERROR:Choose a valid input." << endl;
			  }
			  break;
		}
		case 5:
			return 0;
		default:
			cout << "ERROR: Choose a valid input" << endl;
		}
	}

}