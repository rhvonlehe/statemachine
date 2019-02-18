CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

project(statemachine CXX)

SET(CMAKE_CXX_STANDARD 14)

add_executable(smtest smtest.cpp)

# Make sure we can find boost sml folder (no finder)
target_include_directories(smtest PRIVATE ../sml/include)


