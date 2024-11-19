add_executable(BruteForceTest)

target_sources(
    BruteForceTest
    PUBLIC
    bruteforcetest.cpp
)

target_link_libraries(
    BruteForceTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME BruteForceTest COMMAND BruteForceTest)