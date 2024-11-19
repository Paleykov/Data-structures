#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"
#include "Held-Karp.hpp"

TEST_CASE("Test algorithm")
{
    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    HeldKarp object(matrix);
    object.HeldKarpSolution();

    std::cout << "Test for Held-Karp algorithm" << std::endl;

    const std::vector<int> result = object.getPath();
    REQUIRE(result.size() == 5);
    CHECK(result[0] == 0);
    CHECK(result[1] == 2);
    CHECK(result[2] == 1);
    CHECK(result[3] == 3);
    CHECK(result[4] == 0);
}

TEST_CASE("Test final path construction method") 
{
    std::vector<std::vector<int>> FillerMatrix =
    {
        {0,1,1},
        {1,0,1},
        {1,1,0}
    };

    HeldKarp object(FillerMatrix);

    std::vector<std::vector<std::pair<unsigned, unsigned>>> MemoryTable =
    {
        {{0, 0}, {1, 2}, {2, 3}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
        {{2, 4}, {0, 0}, {2, 6}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
        {{1, 5}, {1, 3}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    };

    unsigned SavedVertex = 1;
    unsigned SavedSet = 5;  

    object.ConstructFinalPath(MemoryTable, SavedVertex, SavedSet);
    std::vector<int> ActualPath = object.getPath();
    ActualPath.push_back(0);

    REQUIRE(ActualPath == std::vector<int>{0, 1, 2, 0});
}

int main(int argc, char* const argv[]) 
{
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
}