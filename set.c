#include "set.h"


void init_set(Set* s) {
    int i;
    for (i = 0; i < 16; i++) {
        s->members[i] = 0;  /* Set each member to 0 */
    }
}


void read_set(int* ptr, Set* s, int n) {
    int* p = ptr;
    int index;
    int x;
    int i;
    init_set(s);  /* Initialize the set before adding elements */
    for (i = 0; i < n; i++) {
        x = *p;  /* Get the current element */
        index = x % 8;  /* Calculate the bit position */
        s->members[x / 8] |= (1 << index);  /* Set the corresponding bit */
        p++;  /* Move to the next element */
    }
}



void print_set(Set s) {
    int i, j;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 8; j++) {
            if (s.members[i] & (1 << j)) {  /* Check if the bit is set */
                printf("%d ", i * 8 + j);  /* Print the element */
            }
        }
    }
    printf("\n");
}



void union_set(Set s1, Set s2, Set* target) {
    int i;
    init_set(target);  /* Initialize the target set */
    for (i = 0; i < 16; i++) {
        target->members[i] = s1.members[i] | s2.members[i];  /* Perform bitwise OR */
    }
}



void intersect_set(Set s1, Set s2, Set* target) {
    int i;
    init_set(target);  /* Initialize the target set */
    for (i = 0; i < 16; i++) {
        target->members[i] = s1.members[i] & s2.members[i];  /* Perform bitwise AND */
    }
}



void sub_set(Set s1, Set s2, Set* target) {
    Set intersected;
    int i;
    intersect_set(s1, s2, &intersected);  /* Find the intersection */
    for (i = 0; i < 16; i++) {
        target->members[i] = s1.members[i] ^ intersected.members[i];  /* Perform bitwise XOR */
    }
}


void symdiff_set(Set s1, Set s2, Set* target) {
    Set intersected;
    intersect_set(s1, s2, &intersected);  /* Find the intersection */
    union_set(s1, s2, target);  /* Find the union */
    sub_set(*target, intersected, target);  /* Subtract the intersection from the union */
}
