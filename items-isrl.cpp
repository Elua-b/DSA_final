#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm>
using namespace std;

#define FILENAME "inventory.csv"

// Item structure
struct Item {
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;

    Item(int id, string name, int qty, string reg_date) {
        item_id = id;
        item_name = name;
        item_quantity = qty;
        item_registration_date = reg_date;
    }
};

// Print items in inventory
void listInventory(vector<Item>& inventory) {
    for (const auto& item: inventory) {
        cout << "ItemID: " << item.item_id << "\tItem Name: " << item.item_name << "\tItem Quantity: " << item.item_quantity << "\tItem Reg Date: " << item.item_registration_date << endl;
    }
}

// Save inventory items to file
void saveInventoryToFile(vector<Item>& inventory, const string& filename) {
    // Open an output file stream to write to
    ofstream file(filename);

    if (file.is_open()) {
        // Write the file header/title first
        file << "ItemID,ItemName,ItemQuantity,ItemRegistrationDate" << endl;

        // Write the item to the file
        for (const auto& item: inventory) {
            file << item.item_id << "," << item.item_name << "," << item.item_quantity << "," << item.item_registration_date << endl;
        }

        cout << "Successfully added inventory item to csv file!" << endl;
        file.close();
    } else {
        cerr << "Unable to open csv file!" << endl;
    }
}

// Load inventory items from file
void loadInventoryFromFile(vector<Item>& inventory, const string& filename) {
    // Open an input file stream to read from
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        getline(file, line); // Skip the header/title of the file

        // Loop through every line of the file
        while (getline(file, line)) {
            // Declare string stream for ever line
            istringstream iss(line);
            string item_id, item_name, item_qty, item_reg_date; // Variable to store chunks from the stream

            if (getline(iss, item_id, ',') && getline(iss, item_name, ',') && getline(iss, item_qty, ',') && getline(iss, item_reg_date, ',')) { // separate each property from the chunk
                inventory.push_back(Item(stoi(item_id), item_name, stoi(item_qty), item_reg_date)); // create a new Item from the chunk and push it to the inventory
            } else {
                cerr << "Error parsing line: " << line << endl;
            }
        }

        file.close();
    } else {
        cerr << "CSV file not available! First create an inventory!" << endl;
    }
}

void sortInventory(vector<Item>& inventory) {
    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
        return a.item_name < b.item_name;
    });
}

int main() {
    try {
        // Initialize inventory vector of type Item {item_id, item_name, item_quantity, item_registration_date}
        vector<Item> inventory;

        // String variable for input
        string input;

        // Continuous loop for allowing input
        while (true) {
            cout << endl << "> ";

            // Get input from cin and store it in the input variable
            getline(cin, input);
            transform(input.begin(), input.end(), input.begin(), ::tolower);
            cout << endl;

            // If input is exit, exit the program
            if (input == "exit") {
                cout << "Exited the program!" << endl;
                break;
            } else if (input == "help") { // If input is help, show the help menu
                cout << "=========================" << endl;
                cout << "Command Syntaxes" << endl;
                cout << "=========================" << endl;
                cout << "itemadd <item_id> <item_name> <item_quantity> <item_registration_date>" << endl;
                cout << "itemlist" << endl;
                continue;
            }

            // Initialiaze a string stream, ss which dissects the input string into small chunks
            stringstream ss(input);
            string arg; // Initialize variable to hold a single chunk of command from the stream

            // Remove items in the inventory vector that were saved in database to avoid doubling values
            inventory.clear();

            vector<string> args; // Vector to hold the commands
            while (ss >> arg) { // Loop through the stream and assign each chunk to arg variable
                args.push_back(arg); // Insert the arg in the args vector
            }

            // Load inventory items from csv file
            loadInventoryFromFile(inventory, FILENAME);

            if (args.size() == 5 && args[0] == "itemadd") { // If command is itemadd
                inventory.push_back(Item(stoi(args[1]), args[2], stoi(args[3]), args[4])); // create an Item structure with parameters from input and add to the inventory vector

                saveInventoryToFile(inventory, FILENAME);
            } else if (args[0] == "itemadd" && args.size() != 5) {
                cerr << "Invalid input parameters!" << endl;
            } else if (args.size() == 1 && args[0] == "itemlist") { // If command is itemlist
                sortInventory(inventory);
                listInventory(inventory);
            } else {
                cout << "Invalid parameters! Run `help` to check command catalog!" << endl;
            }
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}