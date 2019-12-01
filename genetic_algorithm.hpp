//
// Created by humbl on 11/16/2019.
//

#ifndef GENETICALGORITHM_GENETIC_ALGORITHM_HPP
#define GENETICALGORITHM_GENETIC_ALGORITHM_HPP

#include <vector>

#include "tour.hpp"
#include "utils.hpp"

class genetic_algorithm {
private:
    //environment object
    configure cfg;
    //master list
    vector<city> master_list;
    //reports to save every iteration
    vector<report> reports;
    //running population
    vector<tour> population;
    //next generation to be run
    vector<tour> next_population;
    //initial case
    tour base_tour;
    //previous case
    tour prev_tour;
    //solution: best case
    tour best_tour;

    //random number generator
    int random_num(int i);
    //random city name generator
    string random_name(int n);
    //swap genes
    void swap_gene(tour& t);
    //evaluate fitness, but not used, instead using overloaded operator, >
    bool evaluate_fitness(tour & tour1, tour & tour2);
    //current improvement amount (%)
    double improvement;
    //if the user input of improvement factor is achieved
    bool is_improved;

public:
    //iteration number
    static int iteration_no;
    genetic_algorithm() = default;
    genetic_algorithm(configure & cfg);

    void init();
    void run();
    //make report at every iteration
    void make_report();
    //print final report including every iteration result
    void print_result();

    const vector<city> &getMasterList() const;
    const vector<tour> &getPopulation() const;
    void setPopulation(const vector<tour> &population);

    //if the improvement factor is achieved
    bool isImproved() const;
    //evaluate the amount of improvement (%)
    double evaluate_improvement(double mileage1, double mileage2);

    //population initializing
    void init_population(int i);
    //sort population
    void sort_population();
    //generate next population
    void build_new_population();

    //build parents
    vector<vector<tour>> build_parents();
    //crossing parents
    void crossing_parents(vector<vector<tour>> &parents);
    //mutate children genes
    void mutate_gene();

};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
