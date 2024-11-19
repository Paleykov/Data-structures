add_executable(NearestNeighbourTest)

target_sources(
    NearestNeighbourTest
    PUBLIC
    nearestneighbourtest.cpp
)

target_link_libraries(
    NearestNeighbourTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME NearestNeighbourTest COMMAND NearestNeighbourTest)