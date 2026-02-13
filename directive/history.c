#include "../header/history_cmd.h"
#include "../header/types.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


CmdType GetCommandTypeFromString(const char* str)
{
    if (strcmp(str, "guidv4") == 0 || strcmp(str, "GUIDV4") == 0) 
    {
        return GUIDV4;
    } 
    else if (strcmp(str, "guidv7") == 0 || strcmp(str, "GUIDV7") == 0) 
    {
        return GUIDV7;
    } 
    else if (strcmp(str, "ulid") == 0 || strcmp(str, "ULID") == 0) 
    {
        return ULID;
    }
    else 
    {
        return UNKNOWN;
    }
}

void history_help()
{
    printf("Usage: %s history [options]\n", CLI_NAME);
    printf("\t-f, --filter TYPE   Filter history by type (guidv4, guidv7, ulid)\n");
    printf("\t-l, --all          Show all history entries\n");
    printf("\t-h, --help         Show this help message\n");
}

void history_command(int argc, char *argv[])
{   
    if ( argc < 2 || strcmp(argv[1], "-h") == 0  || strcmp(argv[1], "--help") == 0) 
    {
        history_help();
        return;
    } 
    else if (strcmp(argv[1], "-f") == 0  || strcmp(argv[1], "--filter") == 0) 
    {
        CmdType filter_type = GetCommandTypeFromString(argv[2]);
        if (filter_type == UNKNOWN) 
        {
            printf("Unknown filter type: %s\n", argv[2]);
            printf("Valid filter types are: guidv4, guidv7, ulid\n");
            exit(EXIT_FAILURE);
        }

        history_show(filter_type);
    } 
    else if (strcmp(argv[1], "-l") == 0  || strcmp(argv[1], "--all") == 0) 
    {
        history_show(ALL);
    }
    else 
    {
        printf("Unknown option: %s\n", argv[1]);
        history_help();
        exit(EXIT_FAILURE);
    }
}