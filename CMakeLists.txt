# set the minimum cmake version that this project requires
cmake_minimum_required(VERSION 3.22)

# set the name of the project
set(NAME pong_clone)

# set the project name
project(${NAME} C)

# include the resources api
include(cmake/resource.cmake)

# include the pong cmake configuration
include(cmake/pong.cmake)

# set the c language standard
set(CMAKE_C_STANDARD 99)

# add the application
add_app(${NAME})