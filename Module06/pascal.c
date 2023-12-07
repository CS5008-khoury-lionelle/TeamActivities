#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define MAX 5000
#define PRINT_SINGLE 1
#define PRINT_ALL 2

typedef uint64_t ull;

// don't forget to allocate space for your table (multi-demi arrayof MAX x MAX)
static ull table[MAX][MAX];

void printSingleRow(ull *row, int size)
{
    for (int i = 0; i <= size; i++)
    {
        printf("%llu ", row[i]);
    }
    printf("\n");
}

ull pascaldp(int n, int i, int *ops)
{
    if (n == i || i == 0)
    {
        return 1;
    }
    else if (table[n][i] > 0)
    {
        return table[n][i];
    }
    else
    {
        (*ops)++;
        table[n][i] = pascaldp(n - 1, i, ops) + pascaldp(n - 1, i - 1, ops);
        return table[n][i]; // pascal(n - 1, i) + pascal(n - 1, i - 1);
    }
}

ull* pascaldp_full(int n, int *ops)
{
    ull *row = malloc((sizeof(ull)) * (n+1));
    for (int i = 0; i <= n; i++)
    {
        row[i] = pascaldp(n, i, ops);
    }
    return row;
}
ull pascalr(int n, int i, int *ops)
{
    if (n == i || i == 0)
    {
        return 1;
    }
    else
    {
        (*ops)++;
        return pascalr(n - 1, i, ops) + pascalr(n - 1, i - 1, ops);
    }
}

ull* pascalr_full(int n, int *ops)
{
    ull *row = malloc((sizeof(ull)) * (n+1));
    for (int i = 0; i <= n; i++)
    {
        row[i] = pascalr(n, i, ops);
    }
    return row;
}


ull *pascal_iterative(int n, int *ops)
{
    ull **triangle = (ull **)malloc((n + 1) * sizeof(ull *));
    for (int i = 0; i <= n; i++)
    {
        triangle[i] = (ull *)malloc((i + 1) * sizeof(ull));
        triangle[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            (*ops)++;
            if (i == j)
            {
                triangle[i][j] = 1;
            }
            else
            {
                triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
            }
        }
    }
    // copy the last row into a new array to return
    ull *row = malloc((sizeof(ull)) * (n+1));
    for (int i = 0; i <= n; i++)
    {
        row[i] = triangle[n][i];
    }
    // free the triangle
    for (int i = 0; i <= n; i++)
    {
        free(triangle[i]);
    }
    free(triangle);

    // give back the single row
    return row;
}



double time_function(ull* (*func)(int, int *), int n, int *ops, bool print)
{
    // Setup timers
    struct timespec begin, end;
    // Get the time before we start
    clock_gettime(CLOCK_MONOTONIC, &begin);
    ull* row = func(n, ops);
    clock_gettime(CLOCK_MONOTONIC, &end);
    if(print) {
        printSingleRow(row, n);
    }
    return (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
           (end.tv_sec - begin.tv_sec);
}



void help() {
    printf("./pascal.out N [Type] [Print Level]\n");
    printf("\tN is the number of rows in the pascal triangle, required.\n");
    printf("\t[Type] is 4 for dp and iterative only, 3 for all three, 2 for dynamic programming version, 1 for recursive version, 0 for iterative version, defaults to 3.\n");
    printf("\t[Print Level] leave blank for speed compare only, or print to print row\n");

}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("at least two arguments needed!\n");
        help();
        return 1;
    }

    const int n = atoi(argv[1]);
    int type = 3;
    int print = 0;
    if (argc > 2) {
        type = atoi(argv[2]);
    }
    if(argc > 3) {
        print = true;
    }

    int ops;
    double time;
    switch (type)
    {
    case 0:
        printf("iterative version\n");
        ops = 0;
        time = time_function(pascal_iterative, n, &ops, print);
        printf("time: %f(%d)\n", time, ops);
        break;
    case 1:
        printf("recursive version\n");
        ops = 0;
        time = time_function(pascalr_full, n, &ops, print);
        printf("time: %f(%d)\n", time, ops);
        break;
    case 2:
        printf("dynamic programming version\n");
        ops = 0;
        time = time_function(pascaldp_full, n, &ops, print);
        printf("time: %f(%d)\n", time, ops);
        break;
    case 4:
        ops = 0;
        time = time_function(pascal_iterative, n, &ops, print);
        printf("%f,%d,", time, ops);

        ops = 0;
        time = time_function(pascaldp_full, n, &ops, print);
        printf("%f,%d,--", time, ops);
        break;
    default:
        ops = 0;
        time = time_function(pascal_iterative, n, &ops, print);
        printf("%f,%d,", time, ops);

        ops = 0;
        time = time_function(pascaldp_full, n, &ops, print);
        printf("%f,%d,", time, ops);

        ops = 0;
        time = time_function(pascalr_full, n, &ops, print);
        printf("%f,%d", time, ops);

        break;
    }


}
