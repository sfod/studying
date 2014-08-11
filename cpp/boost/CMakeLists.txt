cmake_minimum_required(VERSION 2.8)

project("Boost Studying" CXX)
set(PROJECT "Boost Studying")

set(CMAKE_CXX_FLAGS "-W -Wall -Wextra -Werror -pedantic -std=c++0x -O0 -ggdb")

add_subdirectory(asio)
add_subdirectory(coroutine)
add_subdirectory(signals2)
