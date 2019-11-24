//
// Created by humbl on 11/16/2019.
//
#include <random>
#include <algorithm>
#include <functional>

#include "genetic_algorithm.hpp"

using namespace std;

//constructor with number of city
genetic_algorithm::genetic_algorithm(int numOfCity) {
    double lower = 0.0;
    double upper = 1000.0;

    //random number generator
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(lower, upper);
    auto coordinate_generator = bind(distribution, generator);

    //create cities with randomm coordinates and push to cities list
    for(int i = 0; i < numOfCity; i++) {
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
void genetic_algorithm::make_population(int i) {
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

#include "genetic_algorithm.hpp"
