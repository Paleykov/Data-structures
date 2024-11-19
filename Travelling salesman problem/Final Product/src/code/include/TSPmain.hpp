#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <utility>
#include <chrono>
#include <algorithm>
#include <cmath>

const int MY_INFINITY = std::numeric_limits<int>::max();

class TSPmain
{
protected:
    std::vector<int> path;
    std::vector<std::vector<int>> distancesMatrix;
    double time;

public:
    TSPmain();
    TSPmain(const std::vector<std::vector<int>>&);

    int calculateDistanceHelper(const std::vector<int>& order, const std::vector<std::vector<int>>& distances);
    
    const std::vector<int>& getPath() const;
    void setPath(const std::vector<int>&);

    void printResult(const std::string &name);
    void visualizeSolution(const std::string &fileName);
};