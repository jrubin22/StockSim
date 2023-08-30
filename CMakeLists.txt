#CMakeLists.txt Parent
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
message(STATUS "COMPILING STOCKSIM")

set(MODULE_NAME StockSim)
set(MODULE_VERSION 0.0.1)

project(${MODULE_NAME} VERSION ${MODULE_VERSION} LANGUAGES CXX)

#depends
#find_package(xxx REQUIRED)
add_subdirectory(src)
add_subdirectory(apps)
