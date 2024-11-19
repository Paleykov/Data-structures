#include "CommandReader.hpp"
#include "TSPmain.hpp"
#include "Held-Karp.hpp"
#include "NearestNeighbour.hpp"
#include "TwoOpt.hpp"
#include "BruteForce.hpp"

#include <cstdlib>
#include <ctime> 
#include <direct.h>

class Engine
{
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    std::string currentFileName; 
    bool stopProgram; 
    bool fileIisOpen;
    bool isFileGenerated; 

    Engine(); 

    void findSolutionHK(const std::string taskname); 
    void findSolutionBruteForce(const std::string taskname); 
    void findSolutionNearestNeighbour(const std::string taskname); 
    void findSolutionTwoOpt(std::vector<int> path, const std::string taskname); 

    void printHelp(); 
    void Open(std::string &name); 
    void Close(); 
    void Exit(); 

    bool isCommandValid(CommandReader command); 
    bool isValidFilename(const std::string& filename); 
    bool fileExists(std::string filename);  
    bool isNewFile(const std::string& filename); 
    bool isNumber(const std::string& str); 

    std::vector<std::vector<int>> generateRandomAdjacencyMatrix(const int &maxDistance, const int &size);
    void generateGraph(const int &maxDistance, const int &size);

    void printMatrix() const; 
    void createMap(const std::string &fileName); 

    friend std::istream& operator >> (std::istream& file, std::vector<std::vector<int>> &other); 

public: 
    Engine(const Engine& other) = delete; 
    Engine& operator = (const Engine& other) = delete; 

    static Engine& getInstance(); 

    void DoCommand(CommandReader command); 

    void Exe(); 
};