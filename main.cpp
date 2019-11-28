#include <iostream>
#include <algorithm>
#include "utils.hpp"
#include "genetic_algorithm.hpp"

using namespace std;

void test_steps(configure configure);

int main() {
    //get test information
    string filename = "../config.txt";
    configure cfg;
    readConfig(filename, cfg);

    //print test environment
    cout << "\nThe test setting can be defined at config.txt in program root directory. ";
    cout << "\nThis test is run under the settings below: " << endl;
    cout << cfg << endl;

    //For test each step
    //test_steps(cfg);

    genetic_algorithm algo(cfg);
    algo.init();
    while(genetic_algorithm::iteration_no < cfg.ITERATIONS) {
        algo.run();
    }

    algo.print_result();

    return 0;
}

//test basic steps using print
void test_steps(configure cfg) {
    //prepare test environment
    genetic_algorithm algo(cfg);

    //Test random city generation
    cout << endl << "Test 1: random city generation" << endl << endl;
    for_each(algo.getMasterList().begin(), algo.getMasterList().end(), print_city);

    //make population, test 2 population printing
    cout << endl << "Test 2: population generation - print the last tour" << endl << endl;
    algo.init_population(cfg.POPULATION_SIZE);
    for (int i = 0; i < cfg.POPULATION_SIZE; ++i) {
        if(i == cfg.POPULATION_SIZE - 1) for_each(algo.getPopulation().at(i).getCityList().begin(), algo.getPopulation().at(i).getCityList().end(), print_city);
        cout << algo.getPopulation().at(i) << endl;
    }

    //Test: fitness sort
    cout << endl << "Test 3: fitness sort (print the shortest value)" << endl << endl;
    algo.sort_population();
    cout << endl << algo.getPopulation().at(0) << endl;

    //Test: build new population
    algo.build_new_population();

    //Test: build new population (1st elite)
    cout << endl << "Test 4: print elite" << endl << endl;
    cout << endl << algo.getPopulation().at(0) << endl;
    for_each(algo.getPopulation().at(0).getCityList().begin(), algo.getPopulation().at(0).getCityList().end(), print_city);

    //Test: build new population (print the last tour) - to check generation of new population
    cout << endl << "Test 5: build new population - print the last tour" << endl << endl;
    for (int i = 0; i < cfg.POPULATION_SIZE; ++i) {
        if(i == cfg.POPULATION_SIZE - 1) for_each(algo.getPopulation().at(i).getCityList().begin(), algo.getPopulation().at(i).getCityList().end(), print_city);
        cout << algo.getPopulation().at(i) << endl;
    }
}

