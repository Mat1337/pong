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

    # write the file to the disk
    FILE(WRITE ${HEADER_FILE} "#ifndef ${RESOURCE_NAME_UPPER}_D\n#define ${RESOURCE_NAME_UPPER}_D\n\nextern const char res_${RESOURCE_NAME}_start[]   asm(" \"_binary_${RESOURCE_PATH}_start\"");\nextern const char res_${RESOURCE_NAME}_end[]     asm("\"_binary_${RESOURCE_PATH}_end\"");\n\n#endif // ${RESOURCE_NAME_UPPER}_D\n")
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