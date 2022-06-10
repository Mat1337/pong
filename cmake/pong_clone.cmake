# setup the resources directory
set(RESOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/res")

# setup the sources directory
set(SOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/src")

# macro that creates the application executable
MACRO(ADD_APP name)
    # get all the source files
    file(GLOB_RECURSE SOURCE_LIST "${SOURCES_DIRECTORY}/*.c")

    # create the executable
    add_executable(${name} ${SOURCE_LIST})

    # link all the libraries
    target_link_libraries(${name} freetype glfw glad OpenGL::GL)

    # tell MSVC to use main instead of WinMain for windows subsystem executables
    if (MSVC)
        set_target_properties(${name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif ()

    # copy resources to the build directory
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_HOME_DIRECTORY}/res/" "$<TARGET_FILE_DIR:${name}>/res/")
ENDMACRO()