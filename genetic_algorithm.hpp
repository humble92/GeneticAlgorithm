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
    configure cfg;
    vector<city> master_list;
    vector<report> reports;
    vector<tour> population;
    vector<tour> next_population;
    tour base_tour;
    tour prev_tour;
    tour best_tour;
    int random_num(int i);
    string random_name(int n);
    bool evaluate_fitness(tour & tour1, tour & tour2);

public:
    static int iteration_no;
    genetic_algorithm() = default;
    genetic_algorithm(configure & cfg);

    void init();
    void run();
    void make_report();
    void print_result();

    const vector<city> &getMasterList() const;
    const vector<tour> &getPopulation() const;
    void setPopulation(const vector<tour> &population);

    void init_population(int i);
    void sort_population();
    void build_new_population();

    vector<vector<tour>> build_parents();
    void crossing_parents(vector<vector<tour>> &parents);

    void mutate_gene();
    void swap_gene(tour& t);

    double evaluate_improvement(double mileage1, double mileage2);
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
