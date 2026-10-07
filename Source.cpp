#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Abstract base class
class PantryItem {
protected:
    string name;
    int quantity;
    string expirationDate;

public:
    PantryItem(string n, int q, string e) : name(n), quantity(q), expirationDate(e) {}

    virtual void display() = 0;  // Pure virtual function
    virtual string getType() = 0;  // To identify the type of item
    virtual void save(ofstream& out) = 0;  // Pure virtual function to save data

    string getName() { return name; }
    int getQuantity() { return quantity; }
    string getExpirationDate() { return expirationDate; }
};

// Derived classes
class Grain : public PantryItem {
public:
    Grain(string n, int q, string e) : PantryItem(n, q, e) {}

    void display() override {
        cout << "    + " << name << "\n      - Qty: " << quantity << "\n      - Exp: " << expirationDate << endl;
    }

    string getType() override {
        return "Grain";
    }

    void save(ofstream& out) override {
        out << getType() << " " << name << " " << quantity << " " << expirationDate << endl;
    }
};

class CannedGood : public PantryItem {
public:
    CannedGood(string n, int q, string e) : PantryItem(n, q, e) {}

    void display() override {
        cout << "Canned Good: " << name << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate << endl;
    }

    string getType() override {
        return "CannedGood";
    }

    void save(ofstream& out) override {
        out << getType() << " " << name << " " << quantity << " " << expirationDate << endl;
    }
};

class BakingIngredient : public PantryItem {
public:
    BakingIngredient(string n, int q, string e) : PantryItem(n, q, e) {}

    void display() override {
        cout << "Baking Ingredient: " << name << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate << endl;
    }

    string getType() override {
        return "BakingIngredient";
    }

    void save(ofstream& out) override {
        out << getType() << " " << name << " " << quantity << " " << expirationDate << endl;
    }
};

class Spice : public PantryItem {
public:
    Spice(string n, int q, string e) : PantryItem(n, q, e) {}

    void display() override {
        cout << "Spice: " << name << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate << endl;
    }

    string getType() override {
        return "Spice";
    }

    void save(ofstream& out) override {
        out << getType() << " " << name << " " << quantity << " " << expirationDate << endl;
    }
};

class Snack : public PantryItem {
public:
    Snack(string n, int q, string e) : PantryItem(n, q, e) {}

    void display() override {
        cout << "Snack: " << name << ", Quantity: " << quantity << ", Expiration Date: " << expirationDate << endl;
    }

    string getType() override {
        return "Snack";
    }

    void save(ofstream& out) override {
        out << getType() << " " << name << " " << quantity << " " << expirationDate << endl;
    }
};

// Function to add items to the pantry
void addItem(vector<PantryItem*>& grains, vector<PantryItem*>& cannedGoods, vector<PantryItem*>& bakingIngredients, vector<PantryItem*>& spices, vector<PantryItem*>& snacks) {
    int choice;
    string name, expirationDate;
    int quantity;

    cout << "Choose a category to add an item:\n";
    cout << "1. Grain\n2. Canned Good\n3. Baking Ingredient\n4. Spice\n5. Snack\n";
    cin >> choice;

    cout << "Enter the name of the item: ";
    cin >> name;
    cout << "Enter the quantity: ";
    cin >> quantity;
    cout << "Enter the expiration date (YYYY-MM-DD): ";
    cin >> expirationDate;

    PantryItem* item = nullptr;

    switch (choice) {
    case 1:
        item = new Grain(name, quantity, expirationDate);
        grains.push_back(item);
        break;
    case 2:
        item = new CannedGood(name, quantity, expirationDate);
        cannedGoods.push_back(item);
        break;
    case 3:
        item = new BakingIngredient(name, quantity, expirationDate);
        bakingIngredients.push_back(item);
        break;
    case 4:
        item = new Spice(name, quantity, expirationDate);
        spices.push_back(item);
        break;
    case 5:
        item = new Snack(name, quantity, expirationDate);
        snacks.push_back(item);
        break;
    default:
        cout << "Invalid choice." << endl;
        delete item;
        return;
    }
}

// Function to display items in a specific category
void displayCategory(const vector<PantryItem*>& category, const string& categoryName) {
    if (category.empty()) {
        cout << categoryName << " is empty." << endl;
        return;
    }

    cout << categoryName << " Items:\n";
    for (const auto& item : category) {
        item->display();
    }
}

// Function to save pantry items to a file
void savePantry(const vector<PantryItem*>& pantry) {
    ofstream outFile("pantry.txt", ios::app);
    if (outFile.is_open()) {
        for (const auto& item : pantry) {
            item->save(outFile);
        }
        outFile.close();
    }
    else {
        cout << "Unable to open file for saving." << endl;
    }
}

// Function to save all pantry items to a file
void saveAllPantry(const vector<PantryItem*>& grains, const vector<PantryItem*>& cannedGoods, const vector<PantryItem*>& bakingIngredients, const vector<PantryItem*>& spices, const vector<PantryItem*>& snacks) {
    ofstream outFile("pantry.txt");
    if (outFile.is_open()) {
        for (const auto& item : grains) item->save(outFile);
        for (const auto& item : cannedGoods) item->save(outFile);
        for (const auto& item : bakingIngredients) item->save(outFile);
        for (const auto& item : spices) item->save(outFile);
        for (const auto& item : snacks) item->save(outFile);
        outFile.close();
    }
    else {
        cout << "Unable to open file for saving." << endl;
    }
}

// Function to load pantry items from a file
void loadPantry(vector<PantryItem*>& grains, vector<PantryItem*>& cannedGoods, vector<PantryItem*>& bakingIngredients, vector<PantryItem*>& spices, vector<PantryItem*>& snacks) {
    ifstream inFile("pantry.txt");
    if (inFile.is_open()) {
        string type, name, expirationDate;
        int quantity;
        while (inFile >> type >> name >> quantity >> expirationDate) {
            PantryItem* item = nullptr;
            if (type == "Grain") {
                item = new Grain(name, quantity, expirationDate);
                grains.push_back(item);
            }
            else if (type == "CannedGood") {
                item = new CannedGood(name, quantity, expirationDate);
                cannedGoods.push_back(item);
            }
            else if (type == "BakingIngredient") {
                item = new BakingIngredient(name, quantity, expirationDate);
                bakingIngredients.push_back(item);
            }
            else if (type == "Spice") {
                item = new Spice(name, quantity, expirationDate);
                spices.push_back(item);
            }
            else if (type == "Snack") {
                item = new Snack(name, quantity, expirationDate);
                snacks.push_back(item);
            }
        }
        inFile.close();
    }
    else {
        cout << "No saved pantry items found." << endl;
    }
}

// Function to free allocated memory
void freeMemory(vector<PantryItem*>& pantry) {
    for (auto& item : pantry) {
        delete item;
    }
    pantry.clear();
}

// Function to remove an item from a category
void removeItem(vector<PantryItem*>& category) {
    if (category.empty()) {
        cout << "This category is empty." << endl;
        return;
    }

    cout << "Enter the name of the item to remove: ";
    string name;
    cin >> name;

    auto it = std::find_if(category.begin(), category.end(), [&name](PantryItem* item) {
        return item->getName() == name;
        });

    if (it != category.end()) {
        delete* it;
        category.erase(it);
        cout << "Item removed successfully." << endl;
    }
    else {
        cout << "Item not found." << endl;
    }
}

// Main function
int main() {
    vector<PantryItem*> grains;
    vector<PantryItem*> cannedGoods;
    vector<PantryItem*> bakingIngredients;
    vector<PantryItem*> spices;
    vector<PantryItem*> snacks;

    loadPantry(grains, cannedGoods, bakingIngredients, spices, snacks);
    int choice;

    while (true) {
        cout << "1. Add Item\n2. Display Pantry\n3. Display Category\n4. Remove Item\n5. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            addItem(grains, cannedGoods, bakingIngredients, spices, snacks);
            break;
        case 2:
            displayCategory(grains, "Grains");
            displayCategory(cannedGoods, "Canned Goods");
            displayCategory(bakingIngredients, "Baking Ingredients");
            displayCategory(spices, "Spices");
            displayCategory(snacks, "Snacks");
            break;
        case 3: {
            int catChoice;
            cout << "Choose a category to display:\n";
            cout << "1. Grain\n2. Canned Good\n3. Baking Ingredient\n4. Spice\n5. Snack\n";
            cin >> catChoice;
            switch (catChoice) {
            case 1:
                displayCategory(grains, "Grains");
                break;
            case 2:
                displayCategory(cannedGoods, "Canned Goods");
                break;
            case 3:
                displayCategory(bakingIngredients, "Baking Ingredients");
                break;
            case 4:
                displayCategory(spices, "Spices");
                break;
            case 5:
                displayCategory(snacks, "Snacks");
                break;
            default:
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 4: {
            int catChoice;
            cout << "Choose a category to remove an item from:\n";
            cout << "1. Grain\n2. Canned Good\n3. Baking Ingredient\n4. Spice\n5. Snack\n";
            cin >> catChoice;
            switch (catChoice) {
            case 1:
                removeItem(grains);
                break;
            case 2:
                removeItem(cannedGoods);
                break;
            case 3:
                removeItem(bakingIngredients);
                break;
            case 4:
                removeItem(spices);
                break;
            case 5:
                removeItem(snacks);
                break;
            default:
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 5:
            saveAllPantry(grains, cannedGoods, bakingIngredients, spices, snacks);
            freeMemory(grains);
            freeMemory(cannedGoods);
            freeMemory(bakingIngredients);
            freeMemory(spices);
            freeMemory(snacks);
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }
}
