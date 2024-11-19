#include "TSPmain.hpp"

TSPmain::TSPmain(): path(std::vector<int>{}), distancesMatrix(std::vector<std::vector<int>>{}), time(0)
{}

TSPmain::TSPmain(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty())
    throw std::invalid_argument("Input matrix is empty");

    int NumberOfCities = matrix.size();
    
    distancesMatrix.resize(NumberOfCities, std::vector<int>(NumberOfCities));

    for (int i = 0; i < NumberOfCities; ++i) 
    {
        this->path.push_back(i);
        for (int j = 0; j < NumberOfCities; ++j)
        {
            this->distancesMatrix[i][j] = matrix[i][j];
        }
    }

    time = 0;
}

int TSPmain::calculateDistanceHelper(const std::vector<int>& path, const std::vector<std::vector<int>>& distances) 
{
    int distance = 0;
    for (int i = 0; i < path.size() - 1; ++i) 
    {distance += distances[path[i]][path[i + 1]];}

    distance += distances[path.back()][path[0]];
    return distance;
}

const std::vector<int>& TSPmain::getPath() const
{
    return this->path;
}

void TSPmain::setPath(const std::vector<int>& other)
{
    this->path = other;
}

void TSPmain::printResult(const std::string &name)
{
    std::cout << "The path result from the " + name + " heuristic is: " << std::endl;

    for(int i = 0; i<this->path.size()-1; ++i)
    {
        std::cout << this->path[i] << "-> ";
    }

    std::cout << this->path[this->path.size()-1] << std::endl;
    std::cout << "The distance is: " << calculateDistanceHelper(this->path, this->distancesMatrix) << std::endl;
    std::cout << "The time to calculate is: " << this->time << " seconds." << std::endl;
}

void TSPmain::visualizeSolution(const std::string& fileName) 
{
    std::ofstream dotFile("../../../dots/" + fileName + "_solution.dot");
    if (!dotFile.is_open() || dotFile.fail())
    throw std::runtime_error("Error creating the file!");

    dotFile << "digraph G {\n";
    dotFile << "  layout=neato" << ";\n";

    for (std::size_t i = 0; i < this->distancesMatrix.size(); ++i) 
    {
        for (std::size_t j = i + 1; j < this->distancesMatrix[i].size(); ++j) 
        {
            if (this->distancesMatrix[i][j] != 0) 
            {
                double length = std::sqrt(this->distancesMatrix[i][j]);
                dotFile << "  " << i << " -> " << j << " [len=" << length << ", style=invis, xlabel=\"" << this->distancesMatrix[i][j] << "\"];\n";
            }
        }
    }
    
    for (std::size_t i = 0; i < this->path.size()-1; ++i) 
    {
        int from = this->path[i];
        int to = this->path[i + 1];
        double length = std::sqrt(this->distancesMatrix[from][to]);
        dotFile << "  " << from << " -> " << to << " [len=" << length << ", color=red, label=\"" << this->distancesMatrix[from][to] << "\"];\n";
    }

    dotFile << "}\n";
    dotFile.close();

    std::string DotFilePath = "../../../dots/" + fileName + "_solution.dot";
    std::string PngFilePath = "../../../results/" + fileName + "_solution.png";

    std::string command = std::string("neato") + " -Tpng " + DotFilePath + " -o " + PngFilePath;
    system(command.c_str());        
}
