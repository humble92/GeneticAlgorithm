//
// Created by humbl on 11/24/2019.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#include <vector>
#include "city.hpp"

class tour {
private:
    vector<city> city_list;
    double total_mileage;
    friend bool operator< (const tour& lhs, const tour& rhs);
    friend bool operator> (const tour& lhs, const tour& rhs);
    friend bool operator<=(const tour& lhs, const tour& rhs);
    friend bool operator>=(const tour& lhs, const tour& rhs);
    friend std::ostream& operator<<(std::ostream& os, const tour& obj);

public:
    tour() : total_mileage{0.0} {}
    tour(const vector<city> &cityList);

    void push_back(city);
    vector<city> operator()();
    double get_distance(city & city1, city & city2);
    double get_total_mileage();

    const vector<city> &getCityList() const;

    void setCityList(const vector<city> &cityList);

    void set_total_mileage();
};


#endif //GENETICALGORITHM_TOUR_HPP
