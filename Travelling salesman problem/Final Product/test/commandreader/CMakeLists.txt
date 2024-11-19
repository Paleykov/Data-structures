add_executable(CommandReaderTest)

target_sources(
    CommandReaderTest
    PUBLIC
    commandreadertest.cpp
)

target_link_libraries(
    CommandReaderTest
    PUBLIC
    Catch2::Catch2WithMain
    code
)

add_test(NAME CommandReaderTest COMMAND CommandReaderTest)