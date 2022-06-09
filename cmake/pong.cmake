# set the vendor directory
set(VENDOR_DIRECTORY "${CMAKE_HOME_DIRECTORY}/vendor")

# set the freetype directory
set(FREETYPE_DIRECTORY "${VENDOR_DIRECTORY}/freetype")
set(FREETYPE_INCLUDE "${FREETYPE_DIRECTORY}/include")
set(FREETYPE_LIB "${FREETYPE_DIRECTORY}/${FREETYPE_LIBRARY}")

# set the glew directory
set(GLEW_DIRECTORY "${VENDOR_DIRECTORY}/glew")
set(GLEW_INCLUDE "${GLEW_DIRECTORY}/include")
set(GLEW_LIB "${GLEW_DIRECTORY}/${GLEW_LIBRARY}")
set(GLEW_LIB_DYNAMIC "${GLEW_DIRECTORY}/${GLEW_DYNAMIC}")

# set the glfw directory
set(GLFW_DIRECTORY "${VENDOR_DIRECTORY}/glfw")
set(GLFW_INCLUDE "${GLFW_DIRECTORY}/include")
set(GLFW_LIB "${GLFW_DIRECTORY}/${GLFW_LIBRARY}")
set(GLFW_LIB_DYNAMIC "${GLFW_DIRECTORY}/${GLFW_LIBRARY}/glfw3.dll")

# setup the resources directory
set(RESOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/res")

# setup the sources directory
set(SOURCES_DIRECTORY "${CMAKE_HOME_DIRECTORY}/src")

# macro that creates the application executable
MACRO(ADD_APP name)
    # set the directory for the header files
    include_directories(${FREETYPE_INCLUDE} ${GLEW_INCLUDE} ${GLFW_INCLUDE})

    # set the directory for the library files
    link_directories(${FREETYPE_LIB} ${GLEW_LIB} ${GLFW_LIB})

    # link the libraries
    link_libraries(glfw3dll glew32d opengl32 freetyped)

    # get all the source files
    file(GLOB_RECURSE SOURCE_LIST "${SOURCES_DIRECTORY}/*.c")

    # create the executable
    add_executable(${name} "${SOURCE_LIST}")

    # tell MSVC to use main instead of WinMain for windows subsystem executables
    if (MSVC)
        set_target_properties(${name} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif ()

    # copy all the library natives to the build directory
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLEW_LIB_DYNAMIC}" $<TARGET_FILE_DIR:${name}>)
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy "${GLFW_LIB_DYNAMIC}" $<TARGET_FILE_DIR:${name}>)

    # copy resources to the build directory
    add_custom_command(TARGET ${name} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_HOME_DIRECTORY}/res/" "$<TARGET_FILE_DIR:${name}>/res/")
ENDMACRO()