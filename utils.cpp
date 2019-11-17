//
// Created by humbl on 11/13/2019.
//
#include <cmath>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "utils.hpp"

using namespace std;

double get_distance(city city1, city city2) {
    return sqrt( pow((city1.getX()-city2.getX()), 2) + pow((city1.getY()-city2.getY()), 2));
}

string random_name(int n)
{
    string str("abcdefghijklmnopqrstuvwxyz");
    random_device rd;
    mt19937 generator(rd());
    shuffle(str.begin(), str.end(), generator);
    str[0] = toupper(str[0]); //Capitalize the first character
    int length = n % 5 + 5;

    return str.substr(0, length);    // total length of name
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
