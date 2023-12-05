/// to compile: clang -Wall tester.c -o tester.out

#include <stdio.h>  // Include file for standard input/output
#include <stdlib.h> // so we can use atoi()
#include <time.h>   // so we can use time_t and clock_gettime()
#include <stdbool.h>

#include "sorts.h"

// these are called function pointers
void (*sorts[])(int *, unsigned int, int) = {
    bubbleSortIntegers,
    selectionSortIntegers,
    insertionSortIntegers,
    mergeSortIntegers,
    quickSortIntegers};

int *get_random_array(int size)
{
    // Allocate memory
    int *random = (int *)malloc(sizeof(int) * size);

    // Populate our test data set
    for (int i = 0; i < size; i++)
    {
        // Generate random values from 0 to 99
        random[i] = rand() % size;
    }
    return random;
}

double sort_and_time(int *array, int size, int type, int print)
{
    // Setup timers
    struct timespec begin, end;
    // Get the time before we start
    clock_gettime(CLOCK_MONOTONIC, &begin);
    // Perform the sort
    sorts[type](array, size, print);
    // Get the time after we are done
    clock_gettime(CLOCK_MONOTONIC, &end);

    return (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
           (end.tv_sec - begin.tv_sec);
}

// tests a single sorting algorithm, often best for small runs
void test_one(int type, int size, int print)
{
    int *random = get_random_array(size);

    if (print)
    {
        printf("Before the sort: ");
        printIntArray(random, size);
    }

    double time_taken = sort_and_time(random, size, type, print);

    // Confirm the sort worked
    if (print)
    {
        printf("After the sort : ");
        printIntArray(random, size);
    }

    printf("Total time = %f seconds\n", time_taken);

    // Free our random array
    free(random);
}

// tests a group of algorithms, does not print out the results, just the timings
void test_all(int size)
{
    int *random = get_random_array(size);

    double timings[] = {0, 0, 0, 0, 0};
    for (int i = 0; i < 5; i++)
    {
        timings[i] = sort_and_time(random, size, i, false);
    }

    printf("|%d|%f|%f|%f|%f|%f|", size, timings[0], timings[1], timings[2],
           timings[3], timings[4]);

    free(random);
}

// test just merge_quick since the timings are so much quicker
void test_merge_quick(int size)
{
    int *random = get_random_array(size);

    double timings[] = {0, 0, 0, 0, 0};
    for (int i = 3; i < 5; i++)
    {
        timings[i] = sort_and_time(random, size, i, false);
    }

    printf("|%d|-|-|-|%f|%f|", size, timings[3], timings[4]);

    free(random);
}

int main(int argc, char const *argv[])
{
    // Generate a random seed
    time_t t;
    srand((unsigned)time(&t));

    if (!(argc > 2 && argc < 5))
    {
        printf("Two arguments expected, [sort_type] and random size. Add 1 at the end to print out arrays\n");
        printf("[sort_type] 0 == bubble, 1 == selection, 2 == insertion, 3== merge, 4 == quick, 5={all}, 6={merge,quick}\n");
        printf("Random size determines the total size of the the random array of numbers to be sorted\n");
        printf("\n");
        printf("Example: ./tester.out 0 1000");
        return 1;
    }

    // get teh type of sort
    const int type = atoi(argv[1]);
    if (type > 6)
    {
        printf("invalid type");
        return 1;
    }

    // Convert the argument of the program into an integer
    const int size = atoi(argv[2]);

    if (type == 6)
    {
        test_merge_quick(size);
    }
    else if (type == 5)
    {
        test_all(size);
    }
    else
    {
        int print = 0;
        if (argc == 4)
        {
            print = 1;
        }
        test_one(type, size, print);
    }

    return 0;
}
