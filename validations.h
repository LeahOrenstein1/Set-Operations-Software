#ifndef VALIDATIONS_H
#define VALIDATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SETS 6
#define MAX_COMMAND_LENGTH 100
#define INITIAL_SIZE 100

/**
 * @brief Read a string from standard input with dynamic allocation.
 * @param str Pointer to the string to be allocated and filled.
 */
void read_string(char **str);

/**
 * @brief Manipulate a string by trimming whitespace and ensuring proper comma spacing.
 * @param str Pointer to the string to be manipulated.
 */
void manipulate_string(char **str);

/**
 * @brief Check for multiple consecutive commas in a string.
 * @param str The string to check.
 * @return 9 if consecutive commas found, 0 otherwise.
 */
int check_consecutive_commas(const char *str);

/**
 * @brief Validate the command name.
 * @param command The command string to validate.
 * @return Error number or 0 if valid.
 */
int validate_command_name(const char* command);

/**
 * @brief Check if a string represents an integer.
 * @param str The string to check.
 * @return 0 if integer, -1 if -1, 1 if not an integer.
 */
int is_integer(const char *str);

/**
 * @brief Validate the read_set command.
 * @param command The command string to validate.
 * @return Error number or 0 if valid.
 */
int validate_read_command(const char* command);

/**
 * @brief Validate the print_set command.
 * @param command The command string to validate.
 * @return Error number or 0 if valid.
 */
int validate_print_command(const char* command);

/**
 * @brief Validate a general command (union_set, intersect_set, sub_set, symdiff_set).
 * @param command The command string to validate.
 * @return Error number or 0 if valid.
 */
int validate_general_command(const char* command);

/**
 * @brief Check if a number is within the range 0 to 127.
 * @param str The string representation of the number.
 * @return 1 if in range, 0 otherwise.
 */
int is_number_in_range(const char *str);

/**
 * @brief Extract a substring from a given string.
 * @param str The original string.
 * @param start The starting index.
 * @param end The ending index.
 * @return The extracted substring.
 */
char* get_substring(const char* str, int start, int end);

/**
 * @brief Parse numbers from a string based on valid set names.
 * @param str The string to parse.
 * @return Array of parsed numbers.
 */
int* parse_numbers(const char* str);

/**
 * @brief Count the number of members in an array of numbers.
 * @param numbers The array of numbers.
 * @return The count of numbers before -1.
 */
int count_numbers(const int* numbers);

/**
 * @brief Check if a set name is valid.
 * @param set_name The set name to check.
 * @return Set number + 1 if valid, 0 otherwise.
 */
int is_valid_set(const char *set_name);

/**
 * @brief Check if a command is valid.
 * @param command The command to check.
 * @return Command index + 1 if valid, 0 otherwise.
 */
int is_valid_command(const char *command);

#endif /* FUNCTIONS_H */