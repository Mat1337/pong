set(RC_DEPENDS "")

# generates a header file for the resource
FUNCTION(GENERATE_RESOURCE DIRECTORY INPUT)
    # replace the slashes with spaces so the string can be parsed as arguments
    string(REPLACE "/" " " PARSED_INPUT ${INPUT})

    # parse the string as arguments
    set(INPUT_LIST ${PARSED_INPUT})
    separate_arguments(INPUT_LIST)

    # get the last item from the list
    list(GET INPUT_LIST -1 LAST_ITEM)

    # setup the header file location
    set(HEADER_FILE "${DIRECTORY}/${LAST_ITEM}.h")
    set(SOURCE_FILE "${DIRECTORY}/${LAST_ITEM}.c")

    # setup the resource name
    string(FIND ${LAST_ITEM} "." INDEX)
    string(LENGTH ${LAST_ITEM} ITEM_LEN)
    string(SUBSTRING ${LAST_ITEM} 0 ${INDEX} RESOURCE_NAME)
    string(TOUPPER ${RESOURCE_NAME} RESOURCE_NAME_UPPER)

    # setup the resource path
    string(REPLACE ":" "_" RESOURCE_PATH ${INPUT})
    string(REPLACE "/" "_" RESOURCE_PATH ${RESOURCE_PATH})
    string(REPLACE "-" "_" RESOURCE_PATH ${RESOURCE_PATH})
    string(REPLACE "." "_" RESOURCE_PATH ${RESOURCE_PATH})

    # write the header file to disk
    FILE(WRITE ${HEADER_FILE} "")
    FILE(APPEND ${HEADER_FILE} "#ifndef ${RESOURCE_NAME_UPPER}_D\n")
    FILE(APPEND ${HEADER_FILE} "#define ${RESOURCE_NAME_UPPER}_D\n\n")
    FILE(APPEND ${HEADER_FILE} "const char* get_${RESOURCE_NAME}_start();\n")
    FILE(APPEND ${HEADER_FILE} "const char* get_${RESOURCE_NAME}_end();\n")
    FILE(APPEND ${HEADER_FILE} "long long get_${RESOURCE_NAME}_size();\n\n")
    FILE(APPEND ${HEADER_FILE} "#endif // ${RESOURCE_NAME_UPPER}_D\n")

    # write the source file to disk
    FILE(WRITE ${SOURCE_FILE} "")
    FILE(APPEND ${SOURCE_FILE} "#include \"${LAST_ITEM}.h\"\n")
    FILE(APPEND ${SOURCE_FILE} "#include <stdlib.h>\n\n")
    FILE(APPEND ${SOURCE_FILE} "extern const char* _binary_${RESOURCE_PATH}_start;\n")
    FILE(APPEND ${SOURCE_FILE} "extern const char* _binary_${RESOURCE_PATH}_end;\n\n")
    FILE(APPEND ${SOURCE_FILE} "const char* get_${RESOURCE_NAME}_start() {\n return _binary_${RESOURCE_PATH}_start;\n}\n\n")
    FILE(APPEND ${SOURCE_FILE} "const char* get_${RESOURCE_NAME}_end() {\n return _binary_${RESOURCE_PATH}_end;\n}\n")
    FILE(APPEND ${SOURCE_FILE} "long long get_${RESOURCE_NAME}_size() {\n return (uintptr_t)&_binary_${RESOURCE_PATH}_end - (uintptr_t)&_binary_${RESOURCE_PATH}_start;\n}\n")
ENDFUNCTION()

# function that embeds a resource into the executable
FUNCTION(ADD_RESOURCE INPUT)
    # setup the input identifier
    string(MAKE_C_IDENTIFIER ${INPUT} input_identifier)

    # setup the output location of the output object
    set(OUTPUT "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${input_identifier}.o")

    # link the output object with the executable
    target_link_libraries(${PROJECT_NAME} ${OUTPUT})

    # embed the binary into the executable
    add_custom_command(
            OUTPUT ${OUTPUT}
            COMMAND ${CMAKE_LINKER} -r -b binary -o ${OUTPUT} ${INPUT}
            DEPENDS ${input}
    )

    # setup the resource as a dependency
    set(RC_DEPENDS ${RC_DEPENDS} ${OUTPUT} PARENT_SCOPE)
ENDFUNCTION()