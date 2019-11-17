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

    return 0;
}

