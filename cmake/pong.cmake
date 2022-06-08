# setup the library directory
set(LIBRARY_DIRECTORY "${CMAKE_HOME_DIRECTORY}/lib")

# setup the library include directory
set(LIBRARY_INCLUDE_DIRECTORY "${LIBRARY_DIRECTORY}/include")

# setup the library natives directory
set(LIBRARY_NATIVES_DIRECTORY "${LIBRARY_DIRECTORY}/natives")

# setup the resources directory
set(RESOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/res")

# setup the sources directory
set(SOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/src")

# set the resources include directory
set(RESOURCES_INCLUDE_DIRECTORY "${SOURCES_DIRECTORY}/res")

# macro that creates the application executable
MACRO(ADD_APP name)
    # set the directory for the header files
    include_directories("${LIBRARY_INCLUDE_DIRECTORY}")

    message(${LIBRARY_INCLUDE_DIRECTORY})

    # set the directory for the library files
    link_directories("${LIBRARY_DIRECTORY}")

    # link the libraries
    link_libraries(glfw3 glew32 opengl32 freetype)

    # get all the source files
    file(GLOB_RECURSE SOURCE_LIST "${SOURCES_DIRECTORY}/*.c")

    # create the executable
    add_executable(${name} "${SOURCE_LIST}")

    # tell MSVC to use main instead of WinMain for windows subsystem executables
    if (MSVC)
        set_target_properties(${name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif ()

    # copy all the library natives to the build directory
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${LIBRARY_NATIVES_DIRECTORY}" $<TARGET_FILE_DIR:${name}>)

    # get all the source files
    file(GLOB_RECURSE RESOURCE_LIST "${RESOURCES_DIRECTORY}/*")

    # loop through all the resources
    FOREACH (RESOURCE ${RESOURCE_LIST})
        # and add them resource
        add_resource(${RESOURCE})

        # generate the includes for the resources
        generate_resource(${RESOURCES_INCLUDE_DIRECTORY} ${RESOURCE})
    ENDFOREACH ()

    # add all the resources as the dependencies
    add_custom_target(rc ALL DEPENDS ${RC_DEPENDS})
ENDMACRO()