#pragma once

#include "TSPmain.hpp"

class TwoOpt : public TSPmain
{
public:
    TwoOpt();
    TwoOpt(const std::vector<std::vector<int>>& matrix);

    void doTwoOptExchange(std::vector<int>&, int , int);
    void TwoOptSolution(std::vector<int>&);

    void run(std::vector<int>& initialTour);
};