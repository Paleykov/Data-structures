#pragma once

#include "TSPmain.hpp"

class HeldKarp : public TSPmain
{
public:
    HeldKarp();
    HeldKarp(const std::vector<std::vector<int>>& matrix);

    std::vector<int> ConstructFinalPath(const std::vector<std::vector<std::pair<unsigned, unsigned>>>& MemoryTable, unsigned SavedVertex, unsigned SavedSet);
    void HeldKarpSolution();
    void run();
};