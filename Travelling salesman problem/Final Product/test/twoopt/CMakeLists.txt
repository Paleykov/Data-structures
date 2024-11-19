add_executable(TwoOptTest)

target_sources(
    TwoOptTest
    PUBLIC
    twoopttest.cpp
)

target_link_libraries(
    TwoOptTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME TwoOptTest COMMAND TwoOptTest)