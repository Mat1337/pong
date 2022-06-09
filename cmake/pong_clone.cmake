#################### GLOBAL #####################

# include the external project
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

# set the vendor directory
set(VENDOR_DIRECTORY "${CMAKE_HOME_DIRECTORY}/vendor")

# setup the resources directory
set(RESOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/res")

# setup the sources directory
set(SOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/src")

################### FREETYPE #####################

# set the freetype directory
set(FREETYPE_DIRECTORY "${VENDOR_DIRECTORY}/freetype")

# disable harfbuzz
set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)

# add the freetype directory as a sub directory
add_subdirectory(${FREETYPE_DIRECTORY})

#################### GLFW #####################

# find the opengl package
find_package(OpenGL REQUIRED)

# set the glfw directory
set(GLFW_DIRECTORY "${VENDOR_DIRECTORY}/glfw")

# disable the extra stuff that glfw builds
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add the glfw directory as a sub directory
add_subdirectory(${GLFW_DIRECTORY})

#################### GLAD #####################

# set the flag directory
set(GLAD_DIRECTORY "${VENDOR_DIRECTORY}/glad")

# add the glad directory as a sub directory
add_subdirectory(${GLAD_DIRECTORY})

###############################################

# macro that creates the application executable
MACRO(ADD_APP name)
    # get all the source files
    file(GLOB_RECURSE SOURCE_LIST "${SOURCES_DIRECTORY}/*.c")

    # create the executable
    add_executable(${name} "${SOURCE_LIST}")

    # link all the libraries
    target_link_libraries(${name} freetype glfw glad OpenGL::GL)

    # tell MSVC to use main instead of WinMain for windows subsystem executables
    if (MSVC)
        set_target_properties(${name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif ()

    # copy resources to the build directory
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_HOME_DIRECTORY}/res/" "$<TARGET_FILE_DIR:${name}>/res/")
ENDMACRO()