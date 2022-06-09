# set the minimum cmake version that this project requires
cmake_minimum_required(VERSION 3.22)

# set the c language standard
set(CMAKE_C_STANDARD 99)

# set the name of the project
set(NAME glad)

# set the project name
project(${NAME} C)

# add the library
add_library(${NAME} include/glad/glad.h src/glad.c)

# setup the include directories
target_include_directories(${NAME} PUBLIC include/)