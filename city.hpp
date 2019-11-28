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
    //sequence no of cities
    static int counter;
    int number;
    string name;
    pair<double, double> coordinates;
    friend ostream& operator<<(ostream& out, const city& s);
    friend bool operator==(const city& lhs, const city& rhs);
    void mySwap(city &c1, city &c2);
public:
    city() = default;
    city(string name, pair<double, double> coordinates) : number{++counter}, name{name}, coordinates{ coordinates } { }
    city(string name, double x, double y) : number{++counter}, name{name}, coordinates{ make_pair(x, y) } { }
    int getNumber() const;
    const string &getName() const;
    const pair<double, double> & getCoordinates() const;
    double getX() const;
    double getY() const;

    // Overloading of Assignment Operator
    city& operator=(city other);
};


#endif //GENETICALGORITHM_CITY_HPP
