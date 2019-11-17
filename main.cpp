#include <iostream>
#include <random>
#include <list>
#include <algorithm>
#include <functional>
#include "utils.hpp"

using namespace std;

constexpr int POPULATION = 64;
constexpr double lower = 0.0;
constexpr double upper = 1000.0;

void print(city candidate)
{
    std::cout << candidate << " " << endl;
}


int main() {
    configure cfg;
    string filename = "../config.txt";
    readConfig(filename, cfg);

    //random number generator
    default_random_engine generator(time(0));
    uniform_real_distribution<double> distribution(lower, upper);
    auto coordinate_generator = bind(distribution, generator);

    //create cities with randomm coordinates and push to cities list
    list<city> cities;
    for (int i = 0; i < POPULATION; ++i) {
        city new_city(random_name(i), coordinate_generator(), coordinate_generator());
        cities.push_back(new_city);
    }

    for_each(cities.begin(), cities.end(), print);

    return 0;
}

