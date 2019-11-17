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
    }
}

/*
 * read configure file to set running environment
 * @param string basicString - file path and name
 * @param configure cfg - env. parameters structure
 */
void readConfig(string & basicString, configure  & cfg) {
    string input;
    string token[2];
    int line = 0, i = 0;
    ifstream infile;
    infile.open (basicString);

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
