//
// Created by humbl on 11/13/2019.
//

#include "city.hpp"


int city::counter = 0;

ostream& operator<<(ostream& out, const city& s) {
    out << s.name << " (" << s.coordinates.first << ", " << s.coordinates.second << ")";
    return out;
}

bool operator==(const city& lhs, const city& rhs) { return lhs.getName() == rhs.getName(); }

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
