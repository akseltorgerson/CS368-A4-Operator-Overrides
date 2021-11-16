#include <iostream>
#include <iomanip>
#include "Customer.h"
#include "Drink.h"

using namespace std;

void Customer::Serve(Drink& drink, const STYLE serving_style)
{
    if (drink_count < DRINK_LIMIT)
    {
        drink.Prepare(serving_style);
        drinks[drink_count++] = drink;
    }
}

float Customer::TotalTab(float tip_pct)
{
    float price = 0.0;
    for (int i = 0; i < drink_count; i++)
    {
        price += drinks[i].TotalPrice();
    }
    float tax_val = price*TAX_PCT;
    float tip_val = price*tip_pct/100.0;
    return price + tax_val + tip_val;
}

void Customer::Print(const float tip)
{
    cout << "Your drinks are:" << endl;
    for (int i = 0; i < drink_count; i++)
    {
        drinks[i].Print();
    }
    cout << "***" << endl << fixed << setprecision(2)
         << left << setw(22) << "Tax:"   << TAX_PCT * 100.0 << "%" << endl
         << left << setw(22) << "Tip:"   << tip             << "%" << endl
         << left << setw(22) << "Total:" << "$" << TotalTab(tip)   << endl;
}

bool Customer::ReachedLimit() {
    return drink_count >= DRINK_LIMIT;
}

istream& operator>>(istream& in, Customer& c) {
    in >> c.name;
    in >> c.drink_count;
    for (int i = 0; i < c.drink_count; i++) {
        in >> c.drinks[i];
    }
    return in;
}

ostream& operator<<(ostream& out, Customer& c) {
    out << c.name;
    out << " ";
    out << c.drink_count;
    out << '\n';
    for (int i = 0; i < c.drink_count; i++) {
        out << c.drinks[i] << endl;
    }
}
