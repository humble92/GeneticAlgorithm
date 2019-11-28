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
    vector<city> master_list;
    vector<tour> population;
    vector<tour> next_population;
    configure cfg;
    int random_num(int i);
    string random_name(int n);
    bool evaluate_fitness(tour & tour1, tour & tour2);

public:
    genetic_algorithm() = default;
    genetic_algorithm(configure & cfg);

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
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
