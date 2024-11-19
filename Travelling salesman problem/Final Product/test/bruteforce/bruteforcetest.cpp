#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"
#include "BruteForce.hpp"

TEST_CASE("Test algorithm")
{
    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    BruteForce object(matrix);
    object.BruteForceSolution();

    std::cout << "Test for Brute Force algorithm" << std::endl;

    const std::vector<int> result = object.getPath();
    REQUIRE(result.size() == 5);
    CHECK(result[0] == 0);
    CHECK(result[1] == 2);
    CHECK(result[2] == 1);
    CHECK(result[3] == 3);
    CHECK(result[4] == 0);
}

int main(int argc, char* const argv[]) 
{
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
}