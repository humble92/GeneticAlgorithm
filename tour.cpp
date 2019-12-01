//
// Created by humbl on 11/24/2019.
//
// tour class including all cities in a route and total distance

#include <cmath>

#include "tour.hpp"

//constructor
tour::tour(const vector<city> &cityList) : city_list(cityList) {
    set_total_mileage();
}

// calculate and set total mileage
void tour::set_total_mileage() {
    double total_distance = 0.0;
    vector<city>::size_type i;
    for (i = 0; i < city_list.size() - 1; ++i) {
        total_distance += get_distance(city_list.at(i), city_list.at(i+1));
    }
    total_mileage = total_distance;
}

// return total mileage
double tour::get_total_mileage() {
    return total_mileage;
}

// () operator overloading, the same as getCityList()
vector<city> tour::operator()() {
    return city_list;
}

//return city list vector
const vector<city> &tour::getCityList() const {
    return city_list;
}

//overloading operator<
bool operator< (const tour& lhs, const tour& rhs)
{ return lhs.total_mileage < rhs.total_mileage; }

//overloading operator>
bool operator> (const tour& lhs, const tour& rhs)
{return operator< (rhs,lhs);}

//overloading operator<=
bool operator<=(const tour& lhs, const tour& rhs)
{return !operator> (lhs,rhs);}

//overloading operator>=
bool operator>=(const tour& lhs, const tour& rhs)
{return !operator< (lhs,rhs);}

std::ostream& operator<<(std::ostream& os, const tour& obj)
{
    os << obj.total_mileage;
    return os;
}

// return distance between two cities
double tour::get_distance(city & city1, city & city2) {
    return sqrt( pow((city1.getX()-city2.getX()), 2) + pow((city1.getY()-city2.getY()), 2));
}

// add city to city_list
void tour::push_back(city c) {
    city_list.push_back(c);
}


// set city list vector
void tour::setCityList(const vector<city> &cityList) {
    city_list = cityList;
}
