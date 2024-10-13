#include "validations.h"

const char *VALID_SETS[MAX_SETS] = {"SETA", "SETB", "SETC", "SETD", "SETE", "SETF"};
const char *VALID_COMMANDS[] = {"read_set", "print_set", "union_set", "intersect_set", "sub_set", "symdiff_set", "stop"};

void read_string(char **str) {
    int ch;
    int size = 1; /* Initial minimum size */
    int length = 0;

    *str = malloc(size * sizeof(char));
    if (*str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
        (*str)[length++] = ch;

        /* Check if more memory is needed */
        if (length >= size) {
            size *= 2; /* Double the size */
            char *temp = realloc(*str, size * sizeof(char));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(*str);
                exit(1);
            }
            *str = temp;
        }
    }

    if (ch == EOF) {
        manipulate_string(str);
        if (strcmp("stop", *str) != 0) {
            printf("Error: program ended without the stop command"); 
            exit(1);
        } else {
            exit(0);
        }
    }
            
    (*str)[length] = '\0'; /* Null-terminate the string */
}

void manipulate_string(char **str) {
    char *input = *str;
    int length = strlen(input);
    int start = 0, end = length - 1;

    /* Remove leading whitespace */
    while (isspace((unsigned char)input[start])) {
        start++;
    }

    /* Remove trailing whitespace */
    while (end >= start && isspace((unsigned char)input[end])) {
        end--;
    }

    /* Calculate new length after trimming */
    int new_length = end - start + 1;

    /* Allocate memory for the new string */
    char *temp = malloc((new_length + 1) * sizeof(char));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    /* Copy the trimmed string */
    strncpy(temp, &input[start], new_length);
    temp[new_length] = '\0';

    /* Free the old string memory */
    free(*str);

    /* Handle duplicate whitespace and add space after commas */
    char *result = malloc((2 * new_length + 1) * sizeof(char)); /* Allocate conservatively */
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int j = 0, i = 0;
    int comma_found = 0;

    while (temp[i] != '\0') {
        /* Remove duplicate whitespace */
        if (isspace((unsigned char)temp[i]) && (j == 0 || isspace((unsigned char)result[j - 1]))) {
            i++;
            continue;
        }
        /* Add space after comma and remove whitespace before comma */
        if (temp[i] == ',') {
            if (j > 0 && isspace((unsigned char)result[j - 1]) && !comma_found) {
                j--; /* Remove space before comma if not after another comma */
            }
            result[j++] = ',';
            if (temp[i + 1] != '\0') {
                result[j++] = ' ';
            }
            comma_found = 1; /* Mark that a comma was found */
            i++;
        } else {
            result[j++] = temp[i++];
            comma_found = 0; /* Reset comma found marker */
        }
    }

    /* Remove trailing space if it exists */
    if (j > 0 && isspace((unsigned char)result[j - 1])) {
        j--;
    }

    result[j] = '\0';

    /* Reallocate the string to the exact size */
    *str = realloc(result, (j + 1) * sizeof(char));
    if (*str == NULL) {
        fprintf(stderr, "Memory reallocation failed\n");
        free(result);
        exit(1);
    }

    free(temp);
}

int check_consecutive_commas(const char *str) {
    const char *comma1 = strchr(str, ',');
    while (comma1 != NULL) {
        const char *space = comma1 + 1;
        if (*space == ' ') {
            const char *comma2 = strchr(space + 1, ',');
            if (comma2 != NULL && comma2 == space + 1) {
                return 9; /* Consecutive commas found */
            }
        }
        comma1 = strchr(comma1 + 1, ',');
    }
    return 0; /* No consecutive commas found */
}

int validate_command_name(const char* command) {
    char cmd_name[20] = {0}; /* Temporary buffer to store the command name */
    int i = 0;

    /* Extract command name from input */
    while (command[i] != ' ' && i < strlen(command) && command[i] != ',') {
        cmd_name[i] = command[i];
        i++;
    }

    /* Check for invalid comma in command name */
    if (command[i] == ',') {
        return 11; /* Invalid comma in command name */
    }

    /* Check for specific command names and their validity */
    if (strcmp(cmd_name, "read_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 9 && strcmp(get_substring(cmd_name, 0, 8), "read_set") == 0) {
        return 6; /* Command name too long */
    }

    if (strcmp(cmd_name, "print_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 9 && strcmp(get_substring(cmd_name, 0, 9), "print_set") == 0) {
        return 6; /* Command name too long */
    }

    if (strcmp(cmd_name, "union_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 9 && strcmp(get_substring(cmd_name, 0, 9), "union_set") == 0) {
        return 6; /* Command name too long */
    }

    if (strcmp(cmd_name, "intersect_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 13 && strcmp(get_substring(cmd_name, 0, 13), "intersect_set") == 0) {
        return 6; /* Command name too long */
    }

    if (strcmp(cmd_name, "sub_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 7 && strcmp(get_substring(cmd_name, 0, 7), "sub_set") == 0) {
        return 6; /* Command name too long */
    }

    if (strcmp(cmd_name, "symdiff_set") == 0) {
        return 0; /* Valid command name */
    } else if (i > 11 && strcmp(get_substring(cmd_name, 0, 11), "symdiff_set") == 0) {
        return 6; /* Command name too long */
    }

    if (i > 4 && strcmp(get_substring(cmd_name, 0, 3), "stop") == 0) {
        return 8; /* Command name too long */
    }

    if (strcmp(cmd_name, "stop") == 0) {
        return 0; /* Valid command name */
    }

    return 2; /* Unknown command name */
}

int is_integer(const char *str) {
    int i = 0;
    int length = strlen(str);

    /* Check if the string is empty */
    if (length == 0) {
        return 1;
    }

    /* If the string starts with a minus, skip it */
    if (str[i] == '-') {
        i++;
        /* A string with only a minus is not a number */
        if (length == 1) {
            return 1;
        }
    }

    /* Check if every character in the string is a digit */
    for (; i < length; i++) {
        if (!isdigit(str[i])) {
            return 1;
        }
    }

    /* The string represents an integer, check if it is -1 */
    if (strcmp(str, "-1") == 0) {
        return -1;
    }

    /* The string represents an integer other than -1 */
    return 0;
}

int validate_read_command(const char* command) {
    int i = 15, counter = 0;
    char* set_member;
    if (strlen(command) < 13) {
        if (strcmp(command, "read_set -1") == 0)
            return 7;
        return 1; /* Invalid set name */
    }
    if (is_valid_set(get_substring(command, 9, 13)) == 0)
        return 1; /* Invalid set name */
    if (strlen(command) == 13)
        return 5;
    if (command[13] != ',')
        return 10;
    while (i < strlen(command)) {
        while (!(command[i] == ',' || command[i] == ' ') && i < strlen(command)) {
            counter++;
            i++;
        }
        set_member = get_substring(command, i - counter, i);
        counter = 0;
        if (is_integer(set_member) == 1) /* Invalid set member */
            return 4;
        if (is_integer(set_member) == -1) /* Member -1 */
        {
            if (i != strlen(command)) /* Text after command */
                return 8;
            else return 0;
        }
        if (is_number_in_range(set_member) == 0) /* Not in range */
            return 3;
        if (command[i] != ',') /* Missing comma */
        {
            if (i < strlen(command)) return 10;
            else return 5;
        }
        i += 2;
    }
    return 5;
}

int validate_print_command(const char* command) {
    int valid_set = is_valid_set(get_substring(command, 10, 14)); /* Validate the set name */

    if (!valid_set) {
        return 1; /* Invalid set name */
    }

    if (strlen(command) > 14) {
        return 8; /* Extraneous text after end of command */
    }

    if (strlen(command) == 9) {
        return 7; /* Missing parameter */
    }

    return 0; /* Command is valid */
}

int validate_general_command(const char* command) {
    int i = 0, j = 0, set_count = 0;

    while (i < strlen(command)) {
        if (command[i] == ' ') {
            j = i + 1;
            i++;
            while (command[i] != ' ' && command[i] != ',' && command[i] != '\0') {
                i++;
            }

            if (!is_valid_set(get_substring(command, j, i))) {
                return 1; /* Invalid set name */
            }
            set_count++;
            if (command[i] == '\0') {
                if (set_count == 3) {
                    return 0; /* Command is valid */
                }
                if (set_count > 3) {
                    return 8; /* Too many parameters */
                }
                if (set_count < 3) {
                    return 7; /* Too few parameters */
                }
            }
            if (set_count == 3 && command[i] != '\0') {
                return 8; /* Too many parameters */
            }

            if (command[i] != ',') {
                return 10; /* Missing comma */
            }
        }
        i++;
    }
    if (set_count < 3) {
        return 7; /* Too few parameters */
    }
    return 0; /* Command is valid */
}

int is_number_in_range(const char *str) {
    /* Check if the input string is NULL or empty */
    if (str == NULL || *str == '\0') {
        return 0; /* Invalid input */
    }

    /* Iterate through the string to ensure all characters are digits */
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0; /* Non-digit character found */
        }
    }

    /* Convert the string to an integer */
    int num = atoi(str);

    /* Check if the number is within the range 0 to 127 */
    return (num >= 0 && num <= 127);
}

char* get_substring(const char* str, int start, int end) {
    /* Check for invalid input */
    if (start > end || start < 0 || end > strlen(str)) {
        return NULL; /* Return NULL for invalid input */
    }

    int len = end - start;
    char* substr = (char*)malloc((len + 1) * sizeof(char)); /* Allocate memory for the substring */

    /* Check if memory allocation was successful */
    if (substr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1); /* Exit if memory allocation failed */
    }

    /* Copy the substring */
    strncpy(substr, str + start, len);
    substr[len] = '\0'; /* Null-terminate the substring */

    return substr;
}

int* parse_numbers(const char* str) {
    /* Find the start of the numbers in the input string */
    const char* numbers_start = NULL;
    for (int i = 0; i < MAX_SETS; i++) {
        numbers_start = strstr(str, VALID_SETS[i]);
        if (numbers_start != NULL) {
            numbers_start += strlen(VALID_SETS[i]) + 1; /* Move past the set name and the following space */
            break;
        }
    }

    /* If no valid set name is found, return NULL */
    if (numbers_start == NULL) {
        return NULL;
    }

    /* Count the number of numbers in the string */
    int count = 0;
    const char* temp = numbers_start;
    while (*temp != '\0') {
        if (*temp == ',') {
            count++;
        }
        temp++;
    }
    count++; /* Account for the last number */

    /* Allocate memory for the numbers */
    int* numbers = (int*)malloc((count + 1) * sizeof(int)); /* +1 for the terminator */
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    /* Tokenize the string and convert the tokens to integers */
    char* token;
    char* rest = strdup(numbers_start); /* Create a copy of the numbers string */
    int index = 0;
    token = strtok(rest, ", ");
    while (token != NULL) {
        numbers[index++] = atoi(token);
        token = strtok(NULL, ", ");
    }
    numbers[index] = -1; /* Add terminator */
    free(rest); /* Free the temporary copy of the numbers string */

    return numbers;
}

int count_numbers(const int* numbers) {
    int count = 0;
    /* Iterate through the array until reaching the terminator value -1 */
    while (numbers[count] != -1) {
        count++;
    }
    return count;
}

int is_valid_set(const char *set_name) {
    for (int i = 0; i < MAX_SETS; i++) {
        if (strcmp(set_name, VALID_SETS[i]) == 0) {
            return i + 1; /* Returns set number + 1 */
        }
    }
    return 0;
}

int is_valid_command(const char *command) {
    char cmd[20] = {0}; /* Initialize command buffer */
    int i = 0;

    /* Copy characters from the command string until encountering a space, comma, or end-of-string */
    while (command[i] != ' ' && command[i] != '\0' && command[i] != ',') {
        cmd[i] = command[i];
        i++;
    }
    cmd[i] = '\0'; /* Null-terminate the command buffer */

    /* Check if the command matches any of the valid commands */
    for (int j = 0; j < 7; j++) {
        if (strcmp(cmd, VALID_COMMANDS[j]) == 0) {
            return j + 1; /* Return the index of the valid command */
        }
    }
    return 0; /* Return 0 if the command is not valid */
}