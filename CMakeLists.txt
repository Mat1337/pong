# set the minimum cmake version that this project requires
cmake_minimum_required(VERSION 3.22)

# set the c language standard
set(CMAKE_C_STANDARD 99)

# set the name of the project
set(NAME pong_clone)

# set the project name
project(${NAME} C)

# include the pong cmake configuration
include("cmake/${NAME}.cmake")

# add the application
add_app(${NAME})