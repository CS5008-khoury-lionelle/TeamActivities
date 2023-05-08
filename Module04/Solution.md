# Solution

## Estimator.c
Here is a solution for the run_program function in estimator.c. This is not the only solution, but it is one that works.

```c
    int * counts = calloc(11, sizeof(int));

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    char* line = malloc(BUFF_SIZE * sizeof(char));
    while (fgets(line, BUFF_SIZE, fp) != NULL)
    {
        convertToUpperCase(line);
        for (int i = 0; i < 11; i++)
        {
            if (contains(line, instructions[i]))
            {
                counts[i]++;
            }
        }
    } 

    print_info(counts);

    free(counts);
}
```