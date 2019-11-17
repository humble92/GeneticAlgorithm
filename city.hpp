//
// Created by humbl on 11/13/2019.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#include <utility>
#include <iostream>

using namespace std;

class city {
private:
    static int counter;
    int number;
    string name;
    pair<double, double> coordinates;
    friend ostream& operator<<(ostream& out, const city& s);

public:
    city(string name, pair<double, double> coordinates) : name{name}, number{++counter}, coordinates{ coordinates } { }
    city(string name, double x, double y) : name{name}, number{++counter} , coordinates{ make_pair(x, y) } { }
    int getNumber() const;
    const string &getName() const;
    const pair<double, double> & getCoordinates() const;
    const double getX() const;
    const double getY() const;
};


#endif //GENETICALGORITHM_CITY_HPP
