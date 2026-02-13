#include "../header/ulid_cmd.h"
#include "../header/ulid.h"
#include "../header/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>

void print_and_free_ulids(char **ulids, size_t count)
{
    printf("Generated %zu ULID(s):\n", count);

    for (size_t i = 0; i < count; i++) 
    {
        printf("%zu. %s\n",i+1, ulids[i]);
        free(ulids[i]);
    }

    free(ulids);
}

void ulid_help() 
{
    printf("Usage: %s ulid [options]\n",CLI_NAME);
    printf("\t-n, --count NUM     Number of ULIDs(Default is 1)\n");
    printf("\t-h, --help          Help for ulic command\n");
}

void ulid_command(int argc, char *argv[])
{
    size_t count =1;
    if (argc > 1) 
    {
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0 ||
            ((strcmp(argv[1], "-n") != 0) && (strcmp(argv[1], "--count") != 0)) 
        ) 
        {
            ulid_help();
            return;
        }

        if (argv[2] == NULL) 
        {
            printf("Error: Count value is missing.\n");
            ulid_help();
            exit(EXIT_FAILURE);
        }

        count = atoi(argv[2]);

        if (count <= 0) 
        {
            printf("Invalid count: %zu. Count must be a positive integer.\n", count);
            exit(EXIT_FAILURE);
        }
        else if (count > MAXCOUNT) 
        {
            printf("Count too large: %zu. Please specify a count of %d or less.\n", count, MAXCOUNT);
            exit(EXIT_FAILURE);
        }
    }

    char **ulids = generate_ulid_cmd(count);
    
    print_and_free_ulids(ulids, count);
}