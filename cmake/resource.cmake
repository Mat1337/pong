set(RC_DEPENDS "")

FUNCTION(GENERATE_RESOURCE DIRECTORY INPUT)
    string(REPLACE "/" " " PARSED_INPUT ${INPUT})

    set(INPUT_LIST ${PARSED_INPUT})
    separate_arguments(INPUT_LIST)

    list(GET INPUT_LIST -1 LAST_ITEM)

    set(HEADER_FILE "${DIRECTORY}/${LAST_ITEM}.h")

    string(FIND ${LAST_ITEM} "." INDEX)
    string(LENGTH ${LAST_ITEM} ITEM_LEN)
    string(SUBSTRING ${LAST_ITEM} 0 ${INDEX} RESOURCE_NAME)
    string(TOUPPER ${RESOURCE_NAME} RESOURCE_NAME_UPPER)

    string(REPLACE ":" "_" RESOURCE_PATH ${INPUT})
    string(REPLACE "/" "_" RESOURCE_PATH ${RESOURCE_PATH})
    string(REPLACE "-" "_" RESOURCE_PATH ${RESOURCE_PATH})
    string(REPLACE "." "_" RESOURCE_PATH ${RESOURCE_PATH})

    FILE(WRITE ${HEADER_FILE} "#ifndef ${RESOURCE_NAME_UPPER}_D\n#define ${RESOURCE_NAME_UPPER}_D\n\nextern const char res_${RESOURCE_NAME}_start[]   asm("\"_binary_${RESOURCE_PATH}_start\"");\nextern const char res_${RESOURCE_NAME}_end[]     asm("\"_binary_${RESOURCE_PATH}_end\"");\n\n#endif // ${RESOURCE_NAME_UPPER}_D\n")
ENDFUNCTION()

FUNCTION(ADD_RESOURCE INPUT)
    string(MAKE_C_IDENTIFIER ${INPUT} input_identifier)
    set(OUTPUT "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${input_identifier}.o")
    target_link_libraries(${PROJECT_NAME} ${OUTPUT})

    add_custom_command(
            OUTPUT ${OUTPUT}
            COMMAND ${CMAKE_LINKER} -r -b binary -o ${OUTPUT} ${INPUT}
            DEPENDS ${input}
    )

    set(RC_DEPENDS ${RC_DEPENDS} ${OUTPUT} PARENT_SCOPE)
ENDFUNCTION()