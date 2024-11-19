add_library(code)

target_include_directories(
    code
    PUBLIC
    include/
)

target_sources(
    code
    PUBLIC
    BruteForce.cpp
    Engine.cpp
    Held-Karp.cpp 
    NearestNeighbour.cpp 
    TSPmain.cpp 
    TwoOpt.cpp
    CommandReader.cpp
)