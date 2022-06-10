//
// Created by mat on 6/10/2022.
//

#include "log.h"

// used for accessing the log file
FILE *log_file;

/**
 * Initializes the logging system
 *
 * @param file_name name of the file that you want to save the logs to
 * @return 0 = success, 1 = failed
 */

int log_initialize(char *file_name) {
    // delete the old log file
    remove(file_name);

    // load the file handle
    log_file = fopen(file_name, "a");
    if (log_file == NULL) {
        return 1;
    }

    // print to the file that this is the log file
    fprintf(log_file, "#################################\n");
    fprintf(log_file, "#            Log file           #\n");
    fprintf(log_file, "#################################\n\n");

    // return 0 meaning everything went well
    return 0;
}

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

    // print the message to the file
    vfprintf(log_file, data, arg_list);

    // end the va list
            va_end(arg_list);
    free(data);
}

/**
 * Frees the logging system from memory
 */


void log_free() {
    // close the log file
    fclose(log_file);
}