//
// Created by humbl on 11/16/2019.
//
#include <random>
#include <algorithm>
#include <functional>

#include "genetic_algorithm.hpp"

using namespace std;

//constructor with number of city
genetic_algorithm::genetic_algorithm(configure & cfg) : cfg{cfg} {
    double lower = 0.0;
    double upper = 1000.0;

    //random number generator
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(lower, upper);
    auto coordinate_generator = bind(distribution, generator);

    //create cities with randomm coordinates and push to cities list
    for(int i = 0; i < cfg.CITIES_IN_TOUR; i++) {
        city new_city(random_name(i), coordinate_generator(), coordinate_generator());
        master_list.push_back(new_city);
    }
}

// random number generator between 0 ~ n -1
int genetic_algorithm::random_num(int i) { return rand()%i;}

// random city name generator
string genetic_algorithm::random_name(int n)
{
    string str("abcdefghijklmnopqrstuvwxyz");
    random_device rd;
    mt19937 generator(rd());
    shuffle(str.begin(), str.end(), generator);
    str[0] = toupper(str[0]); //Capitalize the first character
    int length = n % 5 + 5;

    return str.substr(0, length);    // total length of name
}

//getter of master_list
const vector<city> &genetic_algorithm::getMasterList() const {
    return master_list;
}

//make population
void genetic_algorithm::init_population(int i) {
    for (int j = 0; j < i; ++j) {
        random_shuffle(master_list.begin(), master_list.end());
        tour t{master_list};
        population.push_back(t);
    }
}

const vector<tour> &genetic_algorithm::getPopulation() const {
    return population;
}

void genetic_algorithm::setPopulation(const vector<tour> &population) {
    genetic_algorithm::population = population;
}

void genetic_algorithm::sort_population() {
    sort(population.begin(), population.end());
}

bool genetic_algorithm::evaluate_fitness(tour & tour1, tour & tour2) {
    return (tour1.get_total_mileage() < tour2.get_total_mileage());
}

void genetic_algorithm::build_new_population() {
    //keep elite for next iteration
    int nElite = cfg.NUMBER_OF_ELITES;
    for (int i = 0; i < nElite; ++i) {
        next_population.push_back(population.at(i));
    }

    //build parents
    vector<vector<tour>> parents = build_parents();
    crossing_parents(parents);

}

vector<vector<tour>> genetic_algorithm::build_parents() {
    int nParent = cfg.NUMBER_OF_PARENTS;
    int nParentPool = cfg.PARENT_POOL_SIZE;

    int l;
    vector<vector<tour>> parents;
    for (int j = 0; j < nParent; ++j) {
        vector<tour> parent;
        for (int k = 0; k < nParentPool; ++k) {
            l = random_num(cfg.POPULATION_SIZE - cfg.NUMBER_OF_ELITES);
            if(k < cfg.NUMBER_OF_ELITES) {
                k--;
                continue;
            }
            tour t = population.at(l);
            parent.push_back(t);
        }
        //fittest one at first
        sort(parent.begin(), parent.end());
        parents.push_back(parent);
    }

    return parents;
}

void genetic_algorithm::crossing_parents(vector<vector<tour>> & parents) {
    int nParentPool = cfg.PARENT_POOL_SIZE;
    int nParents = cfg.NUMBER_OF_PARENTS;
    vector<tour> children_genes;
    for (int k = 0; k < nParents; ++k) {
        vector<tour> parent = parents.at(k);
        tour t = parent.at(0);    //fittest one
        children_genes.push_back(t);
    }

    //crossing up to population size
    int l;
    for (int i = 0; i < cfg.POPULATION_SIZE - cfg.NUMBER_OF_ELITES; ++i) {
        //crossing fittest parent genes

        //Pick a random index and copy all cities up to and including that index from parent 1
        l = random_num(cfg.CITIES_IN_TOUR);
        tour t;
        tour p1 = children_genes.at(0);
        int j;
        for (j = 0; j <= l; ++j) {
            t.push_back(p1.getCityList().at(j));
        }

        //After hitting index 1 of parent 1, start from beginning of parent 2
        tour p2 = children_genes.at(1);
        vector<city> rest_cities(cfg.CITIES_IN_TOUR - t.getCityList().size());
        for (int k = 0; t.getCityList().size() < cfg.CITIES_IN_TOUR; ++k) {
            if(find(t.getCityList().begin(), t.getCityList().end(), p2.getCityList().at(k)) == t.getCityList().end())
            {
                t.push_back(p2.getCityList().at(k));
            }
        }
    }

}

#include "genetic_algorithm.hpp"
