#pragma once

#include "TSPmain.hpp"

class BruteForce : public TSPmain
{
public:
    BruteForce();
    BruteForce(const std::vector<std::vector<int>>& matrix);

    void BruteForceSolution();
    void run();
};