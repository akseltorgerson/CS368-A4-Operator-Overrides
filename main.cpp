#include <iostream>
#include <fstream>
#include "Customer.h"
#include "Drink.h"

using namespace std;

enum MAIN_MENU { ORDER=1, PAY=2, SAVE=3, LOAD=4, EXIT=5 };
// enum DRINK_MENU { WHOLE=1, TWO=2, HEAVY=3, MILKSHAKE=4, MALT=5, SKIM=6, RETURN=7 };

void PrintMain();
void PrintDrinks(Drink menu[], int count);
void PrintStyles();
void PromptName();

int main() {
    int input = 0;
    int drink_choice = 0;
    int style_choice = 0;
    float tip;
    string name;
    int numMenuItems;
    Customer customer;
    Drink next_drink;
    fstream menuStream;
    ofstream saveTabStream;
    Drink* menu;

    // open a file stream to main.txt
    menuStream.open("menu.txt", std::fstream::in);
    if (menuStream.fail()) {
        cout << "Menu failed to open." << endl;
    } else {
        menuStream >> numMenuItems;
        menu = new Drink[numMenuItems];
        // populate the menu array
        string drinkName;
        float basePrice;
        string drinkStyle;
        for (int i = 0; i < numMenuItems; i++) {
            menuStream >> drinkName;
            menuStream >> basePrice;
            menuStream >> drinkStyle;
            menu[i] = Drink(drinkName, basePrice, NEAT);
        }
    }

    PromptName();
    cin >> name;
    customer = Customer(name);
    
    do {
        PrintMain();
        cin >> input;
        while (!cin || input < 1 || input > 5) {
            if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
            cout << "Please enter a valid menu item: ";
            cin >> input;
        }
        // now we have good input, handle the cases:
        switch (input) {
        case ORDER:
            if (customer.ReachedLimit()) {
                cout << "You've reached your limit!" << endl;
            }
            else {
                PrintDrinks(menu, numMenuItems);
                cin >> drink_choice;
                while (!cin || drink_choice < 1 || drink_choice > 6) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> drink_choice;
                }
                PrintStyles();
                cin >> style_choice;
                while (!cin || style_choice < 1 || style_choice > 4) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> style_choice;
                }
                next_drink = Drink(menu[drink_choice-1]); // copy a drink from the menu.
                switch(style_choice) {
                case NEAT:
                    customer.Serve(next_drink, NEAT);
                    break;
                case ROCKS:
                    customer.Serve(next_drink, ROCKS);
                    break;
                case DOUBLE:
                    customer.Serve(next_drink, DOUBLE);
                    break;
                case TALL:
                    customer.Serve(next_drink, TALL);
                    break;
                }
            }
            break;
        case PAY:
            cout << "Please enter your tip percent (%): ";
            cin >> tip;
            while (!cin || tip < 0.0) {
                if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                cout << "Please enter a valid tip percent (%): ";
                cin >> tip;
            }
            customer.Print(tip); // divide tip by 100 to go from percent to proportion
            PromptName();
            cin >> name;
            customer = Customer(name); // reset after paying tab.
            break;
        case SAVE:
            // create a file called name.txt note: name is the customers name
            std::ofstream{name + ".txt"};
            saveTabStream.open(name);
            if (saveTabStream.is_open()) {
                cout << "here4" << endl;
                saveTabStream << customer << endl;
                cout << "here5" << endl;
                saveTabStream.close();
                cout << "here6" << endl;
            }
            break;
        case LOAD:
            break;
        case EXIT:
            break;
        }
    } while (input != EXIT);

    return 0;
}

void PrintMain() {
    cout << "Welcome to the Dairy Bar!" << endl;
    cout << "[" << ORDER << "] Order a Drink" << endl
         << "[" << PAY   << "] Pay Your Tab"  << endl
         << "[" << SAVE  << "] Save Tab For Later" << endl
         << "[" << LOAD  << "] Load Previous Tab" << endl
         << "[" << EXIT  << "] Exit"          << endl
         << "Please enter a menu item: ";
}

void PrintDrinks(Drink menu[], int count) {
    for (int i = 0; i < count; i++) {
        cout << "[" << i+1 << "] " << menu[i].name << endl;
    }
    cout << "[" << count+1 << "] Return to main menu" << endl;
    cout << "Please enter a menu item: ";
}

void PrintStyles() {
    cout << "[" << NEAT   << "] Neat"         << endl
         << "[" << ROCKS  << "] On the Rocks" << endl
         << "[" << DOUBLE << "] Double"       << endl
         << "[" << TALL   << "] Tall"         << endl
         << "Please enter a menu item: ";
}

void PromptName() {
    cout << "Please enter your name: ";
}