#define CATCH_CONFIG_RUNNER
#include "catch2/catch_all.hpp"
#include "CommandReader.hpp"

TEST_CASE("Test number of arguments")
{
    std::cout << "Test to check the correct number of arguments." << std::endl;
    CommandReader cmd("TwoOpt assisted");

    CHECK(cmd.getNumberOfArgs() == 2);
}

TEST_CASE("Test the index operator")
{
    std::cout << "Test to check correct indexation." << std::endl;
    CommandReader cmd("Generate 65 20");

    CHECK(cmd[0] == "generate");
    CHECK(cmd[1] == "65");
    CHECK(cmd[2] == "20");
}

TEST_CASE("Test the command reader function itself")
{
    std::cout << "Test to check the function as a whole." << std::endl;
    CommandReader cmd("fIrsT    second  thiRd FOurTh      fifth        ");

    CHECK(cmd[0] == "first");
    CHECK(cmd[1] == "second");
    CHECK(cmd[2] == "thiRd");
    CHECK(cmd[3] == "FOurTh");
    CHECK(cmd[4] == "fifth");
}

int main(int argc, char* const argv[]) 
{
    int result = Catch::Session().run(argc, argv);

    while (true);
    return result;
}
