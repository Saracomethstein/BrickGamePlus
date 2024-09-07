cmake_minimum_required(VERSION 3.10)
project(BrickGamePlus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/)
include_directories(${CMAKE_SOURCE_DIR}/brick_game/)
include_directories(${CMAKE_SOURCE_DIR}/gui)

add_subdirectory(brick_game)
add_subdirectory(gui)

enable_testing()
add_subdirectory(tests)

install(TARGETS BrickGamePlus DESTINATION bin)
