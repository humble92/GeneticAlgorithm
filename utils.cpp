//
// Created by humbl on 11/13/2019.
//
#include <random>
#include <fstream>
#include <sstream>
#include "utils.hpp"

using namespace std;

// setting env. parameters
void configure::setValue(int idx, int val) {
    switch(idx) {
        case 0: this->CITIES_IN_TOUR = val; break;
        case 1: this->POPULATION_SIZE = val; break;
        case 2: this->SHUFFLES = val; break;
        case 3: this->ITERATIONS = val; break;
        case 4: this->MAP_BOUNDARY = val; break;
        case 5: this->PARENT_POOL_SIZE = val; break;
        case 6: this->MUTATION_RATE = val; break;
        case 7: this->NUMBER_OF_PARENTS = val; break;
        case 8: this->NUMBER_OF_ELITES = val; break;
        case 9: this->MUTATION_TOURS_RATIO = val; break;
    }
}

ostream &operator<<(ostream &os, const configure &configure) {
    os << "---------------------------------" << endl
       << " CITIES_IN_TOUR: " << configure.CITIES_IN_TOUR << endl
       << " POPULATION_SIZE: " << configure.POPULATION_SIZE << endl
       << " SHUFFLES: " << configure.SHUFFLES  << endl
       << " ITERATIONS: " << configure.ITERATIONS  << endl
       << " MAP_BOUNDARY: " << configure.MAP_BOUNDARY  << endl
       << " PARENT_POOL_SIZE: " << configure.PARENT_POOL_SIZE  << endl
       << " MUTATION_RATE: " << configure.MUTATION_RATE  << endl
       << " NUMBER_OF_PARENTS: " << configure.NUMBER_OF_PARENTS  << endl
       << " NUMBER_OF_ELITES: " << configure.NUMBER_OF_ELITES  << endl
       << " MUTATION_TOURS_RATIO: " << configure.MUTATION_TOURS_RATIO << endl
       << "---------------------------------";
    return os;
}

/*
 * read configure file to set running environment
 * @param string filename - file path and name
 * @param configure cfg - env. parameters structure
 */
void readConfig(string & filename, configure  & cfg) {
    string input;
    string token[2];
    int line = 0, i = 0;
    ifstream infile;
    infile.open (filename);

    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,input); // Saves the line in STRING.
        istringstream ss(input);
        i = 0;

        while(std::getline(ss, token[i], ':')) {
            ++i;
        }
        cfg.setValue(line, stoi(token[1]));
        line++;
    }
    infile.close();

}

//test print for city
void print_city(city candidate)
{
    std::cout << candidate << " " << endl;
}

//test print for tour
void print_tour(tour t)
{
    cout << endl << t << endl;
    for(auto j = t.getCityList().begin(); j != t.getCityList().end(); ++j) {
        print_city(*j);
    }
}

//test print for population
void print_population(vector<tour> v)
{
    for(auto i = v.begin(); i != v.end(); ++i) {
        cout << endl << *i << endl;
        for(auto j = i->getCityList().begin(); j != i->getCityList().end(); ++j) {
            print_city(*j);
        }
    }
}
