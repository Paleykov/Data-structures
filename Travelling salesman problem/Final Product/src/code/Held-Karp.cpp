#include "Held-Karp.hpp"

HeldKarp::HeldKarp(): TSPmain(){}

HeldKarp::HeldKarp(const std::vector<std::vector<int>>& matrix) : TSPmain(matrix) {}

std::vector<int> HeldKarp::ConstructFinalPath(const std::vector<std::vector<std::pair<unsigned, unsigned>>>& MemoryTable, unsigned SavedVertex, unsigned SavedSet) 
{
    std::vector<int> FinalPath;
    FinalPath.push_back(0);
    std::pair<unsigned, unsigned> nullPair = std::make_pair(0, 0);

    while (MemoryTable[SavedVertex][SavedSet] != nullPair) 
    {
        FinalPath.push_back(SavedVertex);

        unsigned NewVertex = MemoryTable[SavedVertex][SavedSet].first;
        unsigned NewSet = MemoryTable[SavedVertex][SavedSet].second;

        SavedVertex = NewVertex;
        SavedSet = NewSet;
    }

    FinalPath.push_back(SavedVertex);
    FinalPath.push_back(0);

    return FinalPath;
}

void HeldKarp::HeldKarpSolution() 
{
    unsigned vertices = this->distancesMatrix.size(); 
    unsigned limit = (1u << vertices) - 1; 

    std::vector<std::vector<double>> DynamicProgramming(vertices,std::vector<double>(limit, std::numeric_limits<double>::max()));
    std::vector<std::vector<std::pair<unsigned, unsigned>>> MemoryTable(vertices,std::vector<std::pair<unsigned, unsigned>>(limit, std::make_pair(0, 0)));

    for (unsigned i = 1; i < vertices; ++i) 
    {
        DynamicProgramming[i][1u << i] = this->distancesMatrix[0][i];
    }

    for (unsigned set = 2; set <= limit; ++set) 
    {
        for (unsigned last = 1; last < vertices; ++last) 
        {
            if (set & (1u << last)) 
            {
                unsigned NewSet = set ^ (1u << last);

                for (unsigned LastTwo = 1; LastTwo < vertices; ++LastTwo) 
                {
                    if (last != LastTwo && (NewSet & (1u << LastTwo))) 
                    {
                        double weight = this->distancesMatrix[LastTwo][last];

                        if (DynamicProgramming[last][set] > DynamicProgramming[LastTwo][NewSet] + weight) 
                        {
                            DynamicProgramming[last][set] = DynamicProgramming[LastTwo][NewSet] + weight;
                            MemoryTable[last][set] = std::make_pair(LastTwo, NewSet);
                        }
                    }
                }
            }
        }
    }

    double MinCost = std::numeric_limits<double>::max();
    unsigned SavedVertex, SavedSet = limit - 1;

    for (unsigned i = 1; i < vertices; ++i) 
    {
        double weight = this->distancesMatrix[i][0];
        double current = DynamicProgramming[i][limit - 1] + weight;

        if (MinCost > current) 
        {
            MinCost = current;
            SavedVertex = i;
        }
    }

    this->path = ConstructFinalPath(MemoryTable, SavedVertex, SavedSet);
}

void HeldKarp::run()
{
    clock_t begin = clock();
    HeldKarpSolution();
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    this->time = time_spent;
}

