//
// Created by humbl on 11/16/2019.
//

#ifndef GENETICALGORITHM_GENETIC_ALGORITHM_HPP
#define GENETICALGORITHM_GENETIC_ALGORITHM_HPP

#include <vector>

#include "tour.hpp"

class genetic_algorithm {
private:
    vector<city> master_list;
    vector<tour> population;
    int random_num(int i);
    string random_name(int n);
    bool evaluate_fitness(tour & tour1, tour & tour2);

public:
    genetic_algorithm() = default;
    genetic_algorithm(int numOfCity);

    const vector<city> &getMasterList() const;
    const vector<tour> &getPopulation() const;
    void setPopulation(const vector<tour> &population);

    void make_population(int i);
    void sort_population();

};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
