#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"
#include "TwoOpt.hpp"

TEST_CASE("Test algorithm - not assisted")
{
    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    std::vector<int> initial = {0,1,2,3,0};
    TwoOpt object(matrix);
    object.TwoOptSolution(initial);

    std::cout << "Test for TwoOpt algorithm - not assisted" << std::endl;

    const std::vector<int> result = object.getPath();
    REQUIRE(result.size() == 5);
    CHECK(result[0] == 0);
    CHECK(result[1] == 2);
    CHECK(result[2] == 1);
    CHECK(result[3] == 3);
    CHECK(result[4] == 0);
}

TEST_CASE("Test algorithm - assisted")
{
    std::vector<std::vector<int>> matrix =
    {
        {0, 10, 15, 20},
        {10, 0, 12, 18},
        {15, 12, 0, 25},
        {20, 18, 25, 0},
    };

    std::vector<int> initial = {0,2,1,3,0};
    TwoOpt object(matrix);
    object.TwoOptSolution(initial);

    std::cout << "Test for TwoOpt algorithm - assisted" << std::endl;

    const std::vector<int> result = object.getPath();
    REQUIRE(result.size() == 5);
    CHECK(result[0] == 0);
    CHECK(result[1] == 2);
    CHECK(result[2] == 1);
    CHECK(result[3] == 3);
    CHECK(result[4] == 0);
}

TEST_CASE("TwoOpt exchange")
{
    std::vector<int> tour = {0, 1, 2, 3, 0};

    TwoOpt object;
    object.setPath(tour);
    object.doTwoOptExchange(tour, 1, 3);

    std::vector<int> expectedTour = {0,3,2,1,0};

    std::cout << "Test for TwoOpt exchange" << std::endl;
    CHECK(tour == expectedTour);
}

int main(int argc, char* const argv[]) 
{
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
}