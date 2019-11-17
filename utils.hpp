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

    void setValue(int idx, int val);
};

//util methods
void readConfig(string & basicString, configure & cfg);


#endif //GENETICALGORITHM_UTILS_HPP