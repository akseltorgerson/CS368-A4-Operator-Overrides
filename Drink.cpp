#include <iomanip>
#include <iostream>
#include <string>
#include "Drink.h"

Drink::Drink() : name(""), base_price(0.0), style(NEAT) {}

Drink::Drink(string _name, float _price, STYLE _style) : name(_name), base_price(_price), style(_style) {}

Drink::Drink(const Drink& copy_from) {
    name = copy_from.name;
    base_price = copy_from.base_price;
    style = copy_from.style;
}

void Drink::Prepare(const STYLE serving_style) {
    style = serving_style;
}

float Drink::TotalPrice()
{
    switch (style)
    {
    case NEAT:
        return base_price;
        break;
    case ROCKS:
        return base_price + 0.25;
        break;
    case DOUBLE:
        return base_price * 2.0;
        break;
    case TALL:
        return base_price + 1.0;
        break;
    default:
        return 0.0; // quiet compiler warning by adding a default case, which should never get used.
    }
}

void Drink::Print() {
    string kind;
    switch (style)
    {
    case NEAT:
        kind = "neat";
        break;
    case ROCKS:
        kind = "rocks";
        break;
    case DOUBLE:
        kind = "double";
        break;
    case TALL:
        kind = "tall";
        break;
    }
    string name_str = name + " (" + kind + "):";
    cout << left << setw(22) <<  name_str << "$" << fixed << setprecision(2) << setw(4) << TotalPrice() << endl;
}

istream& operator>>(istream& in, Drink& d) {
    string style;
    in >> d.name;
    in >> d.base_price;
    in >> style;
    if (style == "NEAT") {
        d.style = NEAT;
    } else if (style == "ROCKS") {
        d.style = ROCKS;
    } else if (style == "DOUBLE") {
        d.style = DOUBLE;
    } else {
        d.style = TALL;
    }
    return in;
}

ostream& operator<<(ostream& out, Drink& d) {
    string style;
    out << d.name;
    out << " ";
    out << d.base_price;
    switch (d.style) {
        case NEAT:
            out << "NEAT";
            break;
        case ROCKS:
            out << "ROCKS";
            break;
        case DOUBLE:
            out << "DOUBLE";
            break;
        case TALL:
            out << "TALL";
            break;
        default:
            break;
    }
    out << '\n';
    return out;
}

