add_executable(TSPmainTest)

target_sources(
    TSPmainTest
    PUBLIC
    tspmaintest.cpp
)

target_link_libraries(
    TSPmainTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME TSPmainTest COMMAND TSPmainTest)