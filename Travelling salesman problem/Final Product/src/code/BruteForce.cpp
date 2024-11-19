#include "BruteForce.hpp"

BruteForce::BruteForce(): TSPmain(){}

BruteForce::BruteForce(const std::vector<std::vector<int>>& matrix) : TSPmain(matrix) {}

void BruteForce::BruteForceSolution() 
{
    int NumberOfCities = this->distancesMatrix.size();
    std::vector<int> cities(NumberOfCities);

    for (int i = 0; i < NumberOfCities; ++i) 
    {cities[i] = i;}

    std::vector<int> OptimalOrder;
    int MinDistance = MY_INFINITY;

    do 
    {
        int distance = calculateDistanceHelper(cities, this->distancesMatrix);
        if (distance < MinDistance) 
        {
            MinDistance = distance;
            OptimalOrder = cities;
        }
    } while (next_permutation(cities.begin(), cities.end()));

    OptimalOrder.push_back(0);
    this->path = OptimalOrder;
}

void BruteForce::run()
{
    clock_t begin = clock();
    BruteForceSolution();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    this->time = time_spent;
}



