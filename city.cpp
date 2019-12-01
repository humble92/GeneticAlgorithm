//
// Created by humbl on 11/13/2019.
//
// city class including city name and its coordinates

#include "city.hpp"


int city::counter = 0;

ostream& operator<<(ostream& out, const city& s) {
    out << s.name << " (" << s.coordinates.first << ", " << s.coordinates.second << ")";
    return out;
}

bool operator==(const city& lhs, const city& rhs) { return lhs.getName() == rhs.getName(); }

city& city::operator=(city other ) {
    mySwap(*this, other);
    return *this;
}

void city::mySwap(city &c1, city &c2) {
    using std::swap;
    swap(c1.number, c2.number);
    swap(c1.name, c2.name);
    swap(c1.coordinates, c2.coordinates);
}

int city::getNumber() const {
    return number;
}

const string & city::getName() const {
    return name;
}

const pair<double, double> & city::getCoordinates() const {
    return coordinates;
}

double city::getX() const {
    return coordinates.first;
}

double city::getY() const {
    return coordinates.second;
}
