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
    vector<vector<city>> population;

public:
    genetic_algorithm() = default;
    genetic_algorithm(int numOfCity);
    double get_distance(city city1, city city2);
    int random_num(int i);
    string random_name(int n);
    void make_population(int i);
    const vector<city> &getMasterList() const;

    const vector<vector<city>> &getPopulation() const;

    void setPopulation(const vector<vector<city>> &population);
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
