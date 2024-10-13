#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "validations.h"


/*
 * File Name: myset.c
 * Description: 
 * This file contains the implementation of set management operations.
 * The operations include adding, removing, membership checking, and
 * performing set operations such as union, intersection, and difference.
 * All operations are performed on the data type defined in the header 
 * file set.h.
 * 
 * Author: Leah Orenstein
 * June 2024
 */



/**
 * @brief Print error message based on error code.
 * @param error_code The error code to print a message for.
 */
void print_error(int error_code);

int main() {
    Set sets[MAX_SETS] = {0};
    Set *result_set;
    Set set1, set2;
    char *command_string = NULL;
    int error, command_type, num_elements;
    int *elements;

    while (1) {
        printf("Enter a command: ");
        read_string(&command_string);
        
        printf("%s\n", command_string);
        
        manipulate_string(&command_string);

        error = validate_command_name(command_string);
        if (error != 0) {
            print_error(error);
            continue;
        }

        error = check_consecutive_commas(command_string);
        if (error == 9) {
            print_error(error);
            continue;
        }

        command_type = is_valid_command(command_string);

        if (command_type == 1) { /* read_set command */
            error = validate_read_command(command_string);
            if (error != 0) {
                print_error(error);
                continue;
            }
            result_set = &sets[is_valid_set(get_substring(command_string, 9, 13)) - 1];
            elements = parse_numbers(command_string);
            if (elements == NULL) {
                printf("Error parsing numbers.\n");
                continue;
            }
            num_elements = count_numbers(elements);
            read_set(elements, result_set, num_elements);
            free(elements);
            continue;
        } else if (command_type == 2) { /* print_set command */
            error = validate_print_command(command_string);
            if (error != 0) {
                print_error(error);
                continue;
            }
            set1 = sets[is_valid_set(get_substring(command_string, 10, 14)) - 1];
            print_set(set1);
            continue;
        } else if (command_type == 7) { /* stop command */
            break;
        } else { /* other set operations */
            error = validate_general_command(command_string);
            if (error != 0) {
                print_error(error);
                continue;
            }

            if (command_type == 3) { /* union_set */
                set1 = sets[is_valid_set(get_substring(command_string, 10, 14)) - 1];
                set2 = sets[is_valid_set(get_substring(command_string, 16, 20)) - 1];
                result_set = &sets[is_valid_set(get_substring(command_string, 22, 26)) - 1];
                union_set(set1, set2, result_set);
            } else if (command_type == 4) { /* intersect_set */
                set1 = sets[is_valid_set(get_substring(command_string, 14, 18)) - 1];
                set2 = sets[is_valid_set(get_substring(command_string, 20, 24)) - 1];
                result_set = &sets[is_valid_set(get_substring(command_string, 26, 30)) - 1];
                intersect_set(set1, set2, result_set);
            } else if (command_type == 5) { /* sub_set */
                set1 = sets[is_valid_set(get_substring(command_string, 8, 12)) - 1];
                set2 = sets[is_valid_set(get_substring(command_string, 14, 18)) - 1];
                result_set = &sets[is_valid_set(get_substring(command_string, 20, 24)) - 1];
                sub_set(set1, set2, result_set);
            } else if (command_type == 6) { /* symdiff_set */
                set1 = sets[is_valid_set(get_substring(command_string, 12, 16)) - 1];
                set2 = sets[is_valid_set(get_substring(command_string, 18, 22)) - 1];
                result_set = &sets[is_valid_set(get_substring(command_string, 24, 28)) - 1];
                symdiff_set(set1, set2, result_set);
            }
        }
    }

    free(command_string);
    return 0;
}

void print_error(int error_code) {
    switch (error_code) {
        case 1:
            printf("Invalid set name\n");
            break;
        case 2:
            printf("Invalid command name\n");
            break;
        case 3:
            printf("Members out of range (0 - 127)\n");
            break;
        case 4:
            printf("Invalid set member - not an integer\n");
            break;
        case 5:
            printf("List of set members is not terminated correctly\n");
            break;
        case 6:
            printf("Missing space after command name\n");
            break;
        case 7:
            printf("Missing parameter\n");
            break;
        case 8:
            printf("Extraneous text after end of command\n");
            break;
        case 9:
            printf("Multiple consecutive commas\n");
            break;
        case 10:
            printf("Missing comma\n");
            break;
        case 11:
            printf("Illegal comma\n");
            break;
        default:
            break;
    }
}