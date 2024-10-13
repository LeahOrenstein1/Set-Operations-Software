myset: myset.o set.o functions.o
	gcc -pedantic -Wall myset.o set.o functions.o -o myset

myset.o: myset.c set.h functions.h
	gcc -pedantic -Wall -c myset.c -o myset.o

set.o: set.c set.h
	gcc -pedantic -Wall -c set.c -o set.o

functions.o: functions.c functions.h
	gcc -pedantic -Wall -c functions.c -o functions.o
