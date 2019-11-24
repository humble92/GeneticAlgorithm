#include <iostream>
#include <algorithm>
#include "utils.hpp"
#include "genetic_algorithm.hpp"

using namespace std;

constexpr int POPULATION = 64;


void print(city candidate)
{
    std::cout << candidate << " " << endl;
}


int main() {
    //get test information
    configure cfg;
    string filename = "../config.txt";
    readConfig(filename, cfg);

    //prepare test environment
    genetic_algorithm algo(cfg.CITIES_IN_TOUR);
    for_each(algo.getMasterList().begin(), algo.getMasterList().end(), print);

    //make population, test 2 population printing
    algo.make_population(cfg.POPULATION_SIZE);
    for (int i = 0; i < 2; ++i) {
        cout << endl;
        for_each(algo.getPopulation().at(i).getCityList().begin(), algo.getPopulation().at(i).getCityList().end(), print);
    }
    algo.sort_population();

    return 0;
}

