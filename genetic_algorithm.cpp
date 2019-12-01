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
    iteration_no = 0;
    double upper = cfg.MAP_BOUNDARY;

    //random number generator
    default_random_engine generator(time(nullptr));
    uniform_real_distribution<double> distribution(lower, upper);
    auto coordinate_generator = bind(distribution, generator);

    //create cities with random coordinates and push to cities list
    for(int i = 0; i < cfg.CITIES_IN_TOUR; i++) {
        city new_city(random_name(i), coordinate_generator(), coordinate_generator());
        master_list.push_back(new_city);
    }

    prev_tour = base_tour = tour{master_list};
}

//initialize population
void genetic_algorithm::init() {
    //make population
    init_population(cfg.POPULATION_SIZE);
}

//run genetic algorithm
void genetic_algorithm::run() {
    //fitness sort
    sort_population();

    //make a report
    make_report();

    //generate new population
    build_new_population();
}

//make each iteration report
void genetic_algorithm::make_report() {
    best_tour = population.at(0);
    double step_improvement = evaluate_improvement(prev_tour.get_total_mileage(), best_tour.get_total_mileage());
    bool step_improved = step_improvement > 0;
    improvement = evaluate_improvement(base_tour.get_total_mileage(), best_tour.get_total_mileage());
    is_improved = improvement >= cfg.IMPROVEMENT_FACTOR;
    report r = report{++iteration_no, best_tour, is_improved, improvement, step_improved, step_improvement};
    reports.push_back(r);
}

//print the whole result including every iteration
void genetic_algorithm::print_result() {
    for_each(reports.begin(), reports.end(), print_report);

    cout << "\n[Final result]\n" << endl;
    cout << "Iteration number: " << iteration_no << endl;
    cout << "Was improvement factor achieved: " << boolalpha << is_improved << " (" << improvement << " %)"<< endl;
    cout << "Base tour distance: " << base_tour << endl;
    cout << "Best tour distance: " << best_tour << endl;
    cout << "Base route: " << endl; print_tour(base_tour);
    cout << "Best route: " << endl; print_tour(best_tour);
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

//getter of population
const vector<tour> &genetic_algorithm::getPopulation() const {
    return population;
}

//setter of population
void genetic_algorithm::setPopulation(const vector<tour> &population) {
    genetic_algorithm::population = population;
}

//sort population
void genetic_algorithm::sort_population() {
    sort(population.begin(), population.end());
}

//to support evaluating fitness, it is replaced with overloaded operator, >
bool genetic_algorithm::evaluate_fitness(tour & tour1, tour & tour2) {
    return (tour1.get_total_mileage() < tour2.get_total_mileage());
}

//build next population
void genetic_algorithm::build_new_population() {
    //keep elite for next iteration
    int nElite = cfg.NUMBER_OF_ELITES;
    for (int i = 0; i < nElite; ++i) {
        next_population.push_back(population.at(i));
    }

    //build parents
    vector<vector<tour>> parents = build_parents();
    crossing_parents(parents);
    mutate_gene();

    prev_tour = population.at(0);
    population.swap(next_population);
    next_population.clear();
}

//build parents
vector<vector<tour>> genetic_algorithm::build_parents() {
    int nParent = cfg.NUMBER_OF_PARENTS;
    int nParentPool = cfg.PARENT_POOL_SIZE;

    int l;
    vector<vector<tour>> parents;
    for (int j = 0; j < nParent; ++j) {
        vector<tour> parent;
        for (int k = 0; k < nParentPool; ++k) {
            l = random_num(cfg.POPULATION_SIZE - cfg.NUMBER_OF_ELITES);
            //to keep elite
            if(l < cfg.NUMBER_OF_ELITES) {
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
    //test printing
    //for_each(parents.begin(), parents.end(), print_population);
    return parents;
}

//crossing parents
void genetic_algorithm::crossing_parents(vector<vector<tour>> & parents) {
    int nParents = cfg.NUMBER_OF_PARENTS;
    unsigned nCitiesInTour = cfg.CITIES_IN_TOUR;
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
        l = random_num(nCitiesInTour);
        tour t;
        tour p1 = children_genes.at(0);
        int j;
        for (j = 0; j <= l; ++j) {
            t.push_back(p1.getCityList().at(j));
        }

        //After hitting index 1 of parent 1, start from beginning of parent 2
        tour p2 = children_genes.at(1);
        vector<city> rest_cities(nCitiesInTour - t.getCityList().size());
        for (int k = 0; t.getCityList().size() < nCitiesInTour; ++k) {
            if(find(t.getCityList().begin(), t.getCityList().end(), p2.getCityList().at(k)) == t.getCityList().end())
            {
                t.push_back(p2.getCityList().at(k));
            }
        }
        t.set_total_mileage();
        next_population.push_back(t);
    }
    //test printing
    //for_each(next_population.begin(), next_population.end(), print_tour);
}

//mutate genes
void genetic_algorithm::mutate_gene() {
    //exclude elite from mutation
    int nMutation = cfg.POPULATION_SIZE * ( (double) cfg.MUTATION_TOURS_RATIO / 100.0);
    int randomNo;
    for (int j = 0; j < nMutation; ++j) {
        randomNo = random_num(cfg.POPULATION_SIZE);
        if(randomNo < cfg.NUMBER_OF_ELITES) {
            j--;
            continue;
        }
//        cout << "[start] swap target: " << endl;
//        print_tour(next_population.at(j));
        swap_gene(next_population.at(j));
//        cout << "-----------------------" << endl;
//        print_tour(next_population.at(j));
//        cout << "[end] swap done " << endl;
    }
}

//swap city with adjacent one
void genetic_algorithm::swap_gene(tour& t)
{
    int randomNo;
    vector<city> city_list = t.getCityList();
    for(auto j = city_list.begin(); j != city_list.end(); ++j) {
        randomNo = random_num(100 + 1); //max 100%
        if(randomNo <= cfg.MUTATION_RATE) {
            if(j == city_list.begin()) {
                swap(*j, *(j+1));
            } else if(j == city_list.end() - 1) {
                swap(*j, *(j-1));
            } else if(randomNo%2 == 0) {
                swap(*j, *(j+1));
            } else {
                swap(*j, *(j-1));
            }
        }
    }

    //because getCityList() returns constant
    t.setCityList(city_list);
}

// random number generator between 0 ~ n - 1
int genetic_algorithm::random_num(int n) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(0, n-1); // distribution in range [1, i]

    return dist(rng);
}

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

//evaluate the amount of improvement (%)
double genetic_algorithm::evaluate_improvement(double mileage1, double mileage2) {
    return (mileage1 - mileage2) * 100 / mileage1;
}

//decide if the improvement factor is achieved
bool genetic_algorithm::isImproved() const {
    return is_improved;
}

//getter of iteration count
int genetic_algorithm::getIterationNo() const {
    return iteration_no;
}

#include "genetic_algorithm.hpp"
