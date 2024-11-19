add_executable(HeldKarpTest)

target_sources(
    HeldKarpTest
    PUBLIC
    heldkarptest.cpp
)

target_link_libraries(
    HeldKarpTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME HeldKarpTest COMMAND HeldKarpTest)