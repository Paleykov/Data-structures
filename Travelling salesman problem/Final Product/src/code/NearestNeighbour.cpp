#include "NearestNeighbour.hpp"
#include "TSPmain.hpp"

NearestNeighbor::NearestNeighbor(): TSPmain(){}

NearestNeighbor::NearestNeighbor(const std::vector<std::vector<int>>& matrix) : TSPmain(matrix) {}

void NearestNeighbor::NNsolution() 
{
    int NumberOfCities = this->distancesMatrix.size();
    std::vector<bool> VisitedCities(NumberOfCities, false);
    std::vector<int> tour;
    tour.reserve(NumberOfCities);

    int current = 0;
    tour.push_back(current);
    VisitedCities[current] = true;

    for (int i = 1; i < NumberOfCities; ++i) 
    {
        int NearestCity = -1;
        int MinDistance = MY_INFINITY;

        for (int j = 0; j < NumberOfCities; ++j) 
        {
            if (!VisitedCities[j] && this->distancesMatrix[current][j] < MinDistance) 
            {
                MinDistance = this->distancesMatrix[current][j];
                NearestCity = j;
            }
        }

        current = NearestCity;
        tour.push_back(current);
        VisitedCities[current] = true;
    }
    tour.push_back(tour[0]);

    this->path = tour;
}

void NearestNeighbor::run()
{
    clock_t begin = clock();
    NNsolution();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    this->time = time_spent;
}

