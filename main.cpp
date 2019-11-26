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
    genetic_algorithm algo(cfg);

    //Test random city generation
    cout << "Test: random city generation" << endl << endl;
    for_each(algo.getMasterList().begin(), algo.getMasterList().end(), print);

    //make population, test 2 population printing
    cout << endl << "Test: population generation from 1st tour" << endl << endl;
    algo.init_population(cfg.POPULATION_SIZE);
    for (int i = 0; i < cfg.POPULATION_SIZE; ++i) {
        if(i == 0) for_each(algo.getPopulation().at(i).getCityList().begin(), algo.getPopulation().at(i).getCityList().end(), print);
        cout << algo.getPopulation().at(i) << endl;
    }

    //Test: fitness sort
    cout << endl << "Test: fitness sort (print the shortest value)" << endl << endl;
    algo.sort_population();
    cout << algo.getPopulation().at(0);


    return 0;
}

