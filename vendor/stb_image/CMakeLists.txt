# set the minimum cmake version that this project requires
cmake_minimum_required(VERSION 3.22)

# set the c language standard
set(CMAKE_C_STANDARD 99)

# set the name of the project
set(NAME stb_image)

# set the project name
project(${NAME} C)

# add the library
add_library(${NAME} src/stb_image.c include/stb_image.h)

# setup the include directories
target_include_directories(${NAME} PUBLIC include/)