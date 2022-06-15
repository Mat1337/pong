# set the vendor directory
set(VENDOR_DIRECTORY "${CMAKE_HOME_DIRECTORY}/vendor")

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

############### STB_IMAGE #####################

# set the flag directory
set(STB_IMAGE_DIRECTORY "${VENDOR_DIRECTORY}/stb_image")

# add the glad directory as a sub directory
add_subdirectory(${STB_IMAGE_DIRECTORY})

###############################################