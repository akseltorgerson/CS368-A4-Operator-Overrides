#include <string>
// if you need any additional includes, add them here.

#ifndef DRINK_HEADER
#define DRINK_HEADER
using namespace std;

enum STYLE {NEAT=1, ROCKS=2, DOUBLE=3, TALL=4};

struct Drink {
    string name;
    float base_price;
    STYLE style;

    Drink(); // default constructor to make compiler happy when we create array.
    Drink(string _name, float _price, STYLE _style = NEAT);
    Drink(const Drink& copy_from);

    void Prepare(const STYLE serving_style);
    float TotalPrice();
    void Print();
    // data and functions should be added here
    // you can add a private section for data if desired.
    friend istream& operator>>(istream& in, Drink& d);
    friend ostream& operator<<(ostream& out, Drink& d);
};
#endif

