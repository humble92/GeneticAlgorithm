//
// Created by humbl on 11/13/2019.
//

#ifndef GENETICALGORITHM_UTILS_HPP
#define GENETICALGORITHM_UTILS_HPP

#include "city.hpp"

//environment parameters from a config file
struct configure {
    int CITIES_IN_TOUR;
    int POPULATION_SIZE;
    int SHUFFLES;
    int ITERATIONS;
    int MAP_BOUNDARY;
    int PARENT_POOL_SIZE;
    int MUTATION_RATE;
    int NUMBER_OF_PARENTS;
    int NUMBER_OF_ELITES;

    void setValue(int idx, int val) {
        switch(idx) {
            case 0: this->CITIES_IN_TOUR = val; break;
            case 1: this->POPULATION_SIZE = val; break;
            case 2: this->SHUFFLES = val; break;
            case 3: this->ITERATIONS = val; break;
            case 4: this->MAP_BOUNDARY = val; break;
            case 5: this->PARENT_POOL_SIZE = val; break;
            case 6: this->MUTATION_RATE = val; break;
            case 7: this->NUMBER_OF_PARENTS = val; break;
            case 8: this->NUMBER_OF_ELITES = val; break;
        }
    }
};

void readConfig(string & basicString, configure & cfg);
double get_distance(city city1, city city2);
string random_name(int n);

#endif //GENETICALGORITHM_UTILS_HPP
