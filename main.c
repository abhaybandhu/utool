#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include "header/guid.h"
#include "header/history.h"
#include "header/ulid.h"
#include "header/types.h"
#define CLI_VERSION "1.0.0"

void print_help() 
{
    printf("Usage: %s [options]\n", CLI_NAME);
    printf("Options:\n");
    printf("\tguid                Generate GUID(Version 7(default) or 4)\n");
    printf("\tulid                Generate ULID.(NUM default value is 1)\n");
    printf("\tcopy                Copy GUID/UUID to clipboard\n");
    printf("\thistory TYPE        Show history (ALL, GUID, ULID)\n");
    printf("\thelp                Show this help message\n");
    printf("\version              Show cli version\n");
}


int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        print_help();
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "guid") == 0 || strcmp(argv[1], "uuid") == 0) 
    {
        guid_command(argc - 1, argv +1);
    }
    else if (strcmp(argv[1], "ulid") == 0) 
    {
        ulid_command(argc - 1, argv +1);
    }
    else if (strcmp(argv[1], "copy") == 0) 
    {
        // Placeholder for copy command
        printf("Copy command selected\n");
    } 
    else if (strcmp(argv[1], "history") == 0) 
    {
        history_command(argc - 1, argv +1);
    }
    else if (strcmp(argv[1], "version") == 0) 
    {
        printf("%s version %s\n",CLI_NAME, CLI_VERSION);
    } 
    else 
    {
        if (strcmp(argv[1], "help") != 0)
            printf("Unknown command: %s\n", argv[1]);
        print_help();
    }


    return EXIT_SUCCESS;
}


