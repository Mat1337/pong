//
// Created by mat on 6/10/2022.
//

#include "log.h"
#include "list.h"

/**
 * Prints a log into the logging system
 *
 * @param prefix prefix of the log
 * @param format format of the message
 * @param ... arguments of the message
 */

void log_print(char *prefix, char *format, ...) {
    // start the va list
    va_list arg_list;
    va_start(arg_list, format);

    // calculate all the lengths
    int prefix_len = (int) strlen(prefix);
    int format_len = (int) strlen(format);
    int len = prefix_len + format_len;

    // allocate memory for the format and build up the format
    char *data = calloc(len + 2, sizeof(char));
    strcpy(data, prefix);
    strcpy(data + prefix_len, format);
    strcpy(data + len, "\n");

    // print the message to the console
    vprintf(data, arg_list);

    // end the va list
    va_end(arg_list);

    // free the allocated string
    free(data);
}