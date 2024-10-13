#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>

#define SET_SIZE 16

/**
 * @brief Structure representing a set of integers.
 */
typedef struct {
    char members[SET_SIZE];
} Set;

/**
 * @brief Initialize a set.
 * @param s Pointer to the set to be initialized.
 */
void init_set(Set* s);

/**
 * @brief Read integers into a set.
 * @param ptr Pointer to the array of integers to be read.
 * @param s Pointer to the set to store the integers.
 * @param n Number of integers to read.
 */
void read_set(int* ptr, Set* s, int n);

/**
 * @brief Print the contents of a set.
 * @param s The set to be printed.
 */
void print_set(Set s);

/**
 * @brief Perform union operation on two sets.
 * @param s1 First set.
 * @param s2 Second set.
 * @param target Pointer to the set to store the result.
 */
void union_set(Set s1, Set s2, Set* target);

/**
 * @brief Perform intersection operation on two sets.
 * @param s1 First set.
 * @param s2 Second set.
 * @param target Pointer to the set to store the result.
 */
void intersect_set(Set s1, Set s2, Set* target);

/**
 * @brief Perform set subtraction operation.
 * @param s1 First set (minuend).
 * @param s2 Second set (subtrahend).
 * @param target Pointer to the set to store the result.
 */
void sub_set(Set s1, Set s2, Set* target);

/**
 * @brief Perform symmetric difference operation on two sets.
 * @param s1 First set.
 * @param s2 Second set.
 * @param target Pointer to the set to store the result.
 */
void symdiff_set(Set s1, Set s2, Set* target);

#endif /* SET_H */