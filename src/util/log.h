//
// Created by mat on 6/10/2022.
//

#ifndef PONG_CLONE_LOG_H
#define PONG_CLONE_LOG_H

#define MAX_BUFFER_LEN 1024 * 10

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// define all the log types
#define LOG_INFO(...)   log_print("INFO: ", __VA_ARGS__)
#define LOG_WARN(...)   log_print("WARN: ", __VA_ARGS__)
#define LOG_ERROR(...)  log_print("ERROR: ", __VA_ARGS__)

/**
 * Initializes the logging system
 *
 * @param file_name name of the file that you want to save the logs to
 * @return 0 = success, 1 = failed
 */

int log_initialize(char *file_name);

/**
 * Prints a log into the logging system
 *
 * @param prefix prefix of the log
 * @param format format of the message
 * @param ... arguments of the message
 */

void log_print(char *prefix, char *format, ...);

/**
 * Frees the logging system from memory
 */

void log_free();

#endif //PONG_CLONE_LOG_H
