cmake_minimum_required(VERSION 3.13.0)
project(CmakeTutorial VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${TSP_PROJECT})
set(CPACK_PROJECT_VERSION ${VERSION_1})
include(CPack)