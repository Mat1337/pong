//
// Created by mat on 6/10/2022.
//

#ifndef PONG_CLONE_LOG_H
#define PONG_CLONE_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// define all the log types
#define LOG_INFO(...)   log_print("INFO: ", __VA_ARGS__)
#define LOG_WARN(...)   log_print("WARN: ", __VA_ARGS__)
#define LOG_ERROR(...)  log_print("ERROR: ", __VA_ARGS__)

/**
 * Prints a log into the logging system
 *
 * @param prefix prefix of the log
 * @param format format of the message
 * @param ... arguments of the message
 */

void log_print(char *prefix, char *format, ...);

#endif //PONG_CLONE_LOG_H
