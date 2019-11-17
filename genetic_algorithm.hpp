//
// Created by humbl on 11/16/2019.
//

#ifndef GENETICALGORITHM_GENETIC_ALGORITHM_HPP
#define GENETICALGORITHM_GENETIC_ALGORITHM_HPP

#include <vector>

#include "city.hpp"

class genetic_algorithm {
private:
    vector<city> master_list;

public:
    genetic_algorithm() = default;
    genetic_algorithm(int numOfCity);
    double get_distance(city city1, city city2);
    string random_name(int n);

    const vector<city> &getMasterList() const;
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
