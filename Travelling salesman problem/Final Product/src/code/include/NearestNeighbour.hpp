#pragma once

#include "TSPmain.hpp"

class NearestNeighbor : public TSPmain
{
public:
    NearestNeighbor();
    NearestNeighbor(const std::vector<std::vector<int>>& matrix);

    void NNsolution();
    void run();
};