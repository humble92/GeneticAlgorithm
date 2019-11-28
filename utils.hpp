//
// Created by humbl on 11/13/2019.
//

#ifndef GENETICALGORITHM_UTILS_HPP
#define GENETICALGORITHM_UTILS_HPP

#include <ostream>
#include "city.hpp"
#include "tour.hpp"

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
    int MUTATION_TOURS_RATIO;
    int IMPROVEMENT_FACTOR;

    void setValue(int idx, int val);
    friend ostream &operator<<(ostream &os, const configure &configure);
};

struct report {
    int iteration;
    tour elite_tour;
    bool is_improved;
    double improvement;
    bool step_improved;
    double step_improvement;

    report(int iteration, const tour &eliteTour, bool isImproved, double improvement);

    report(int iteration, const tour &eliteTour, bool isImproved, double improvement, bool stepImproved,
           double stepImprovement);
};

//util methods
void readConfig(string & filename, configure & cfg);

void print_city(city candidate);
void print_tour(tour t);
void print_report(report r);
void print_population(vector<tour> v);

#endif //GENETICALGORITHM_UTILS_HPP
