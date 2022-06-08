include(cmake/resource.cmake)

# setup the resources directory
set(RESOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/res")

# setup the sources directory
set(SOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/src")

# set the resources include directory
set(RESOURCES_INCLUDE_DIRECTORY "${SOURCES_DIRECTORY}/res")

# macro that creates the application executable
MACRO(ADD_APP name)
    # get all the source files
    file(GLOB_RECURSE SOURCE_LIST "${SOURCES_DIRECTORY}/*.c")

    # create the executable
    add_executable(${name} WIN32 "${SOURCE_LIST}")

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