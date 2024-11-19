#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"
#include "TSPmain.hpp"
#include "NearestNeighbour.hpp"
#include <fstream>

std::string readFile(const std::string& filePath) 
{
    std::ifstream file(filePath);
    if (!file.is_open()) 
    {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    file.close();
    return buffer.str();
}

TEST_CASE("Test visualizeSolution function output") 
{
    std::cout << "Test for visualizeSolution function output." << std::endl;

    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    NearestNeighbor tsp(matrix);  
    tsp.run();
    std::string fileName = "test_case";
    tsp.visualizeSolution(fileName);

    std::string outputBuffer = readFile("../../../dots/" + fileName + "_solution.dot");

    std::string expectedOutput = R"(digraph G {
  layout=neato;
  0 -> 1 [len=3.16228, style=invis, xlabel="10"];
  0 -> 2 [len=3.87298, style=invis, xlabel="15"];
  0 -> 3 [len=4.47214, style=invis, xlabel="20"];
  1 -> 2 [len=3.4641, style=invis, xlabel="12"];
  1 -> 3 [len=4.24264, style=invis, xlabel="18"];
  2 -> 3 [len=5, style=invis, xlabel="25"];
  0 -> 1 [len=3.16228, color=red, label="10"];
  1 -> 2 [len=3.4641, color=red, label="12"];
  2 -> 3 [len=5, color=red, label="25"];
  3 -> 0 [len=4.47214, color=red, label="20"];
})";

    expectedOutput = expectedOutput + "\n";

    REQUIRE(outputBuffer == expectedOutput);

    std::remove(("../../../dots/" + fileName + "_solution.dot").c_str());
    std::remove(("../../../results/" + fileName + "_solution.png").c_str());
}

TEST_CASE("Calculate distance function test") 
{
    std::cout << "Test for distance function." << std::endl;
    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    NearestNeighbor tsp(matrix);  
    tsp.run();

    int distance = 0;

    REQUIRE(tsp.calculateDistanceHelper(tsp.getPath(), matrix) == 67);
}

int main(int argc, char* const argv[]) 
{
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
}