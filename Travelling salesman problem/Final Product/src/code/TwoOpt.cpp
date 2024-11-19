#include "TwoOpt.hpp"

TwoOpt::TwoOpt(): TSPmain(){}

TwoOpt::TwoOpt(const std::vector<std::vector<int>>& matrix) : TSPmain(matrix) {}

void TwoOpt::doTwoOptExchange(std::vector<int>& tour, int i, int k)
{
    while (i < k) 
    {
        std::swap(tour[i], tour[k]);
        i++;
        k--;
    }
}

void TwoOpt::TwoOptSolution(std::vector<int>& initialTour) 
{
    int n = initialTour.size();
    std::vector<int> tour = initialTour;
    bool improvement;

    do 
    {
        improvement = false;

        for (int i = 0; i < n - 2; ++i) 
        {
            for (int k = i + 2; k < n; ++k) 
            {
                int PreviousCost = this->distancesMatrix[tour[i]][tour[i + 1]] + this->distancesMatrix[tour[k]][tour[(k + 1) % n]];
                int NewCost = this->distancesMatrix[tour[i]][tour[k]] + this->distancesMatrix[tour[i + 1]][tour[(k + 1) % n]];

                if (NewCost < PreviousCost) 
                {
                    doTwoOptExchange(tour, i + 1, k);
                    improvement = true;
                }
            }
        }
    } while (improvement);

    this->path = tour;
}

void TwoOpt::run(std::vector<int>& initialTour)
{
    clock_t begin = clock();
    TwoOptSolution(initialTour);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    this->time = time_spent;
}
