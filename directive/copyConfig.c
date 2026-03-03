#include "../header/types.h"
#include "../header/config_cmd.h"
#include "../header/copyConfig.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void copy_help()
{
    printf("Usage: %s copy [options]\n", CLI_NAME);
    printf("\t--config\t\tShow Configuration\n");
    printf("\t--SetDefault=TRUE/FALSE\tSet default value\n");
}

void copy_config_command(int argc, char *argv[])
{
    if (argc < 2 || strcmp(argv[1], "--config") == 0) 
    {
        bool is_copy_enabled = getCopyConfig();
        printf("Copy to clipboard is currently %s\n", is_copy_enabled ? "enabled" : "disabled");
        return;
    } 
    else if (strncmp(argv[1], "--SetDefault=", 13) == 0) 
    {
        char *value = argv[1] + 13;
        if (strcmp(value, "TRUE") == 0) 
        {
            setDefaultConfig(true);
            printf("Copy to clipboard has been enabled by default.\n");
        } 
        else if (strcmp(value, "FALSE") == 0) 
        {
            setDefaultConfig(false);
            printf("Copy to clipboard has been disabled by default.\n");
        } 
        else 
        {
            printf("Invalid value for --SetDefault. Use TRUE or FALSE.\n");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        copy_help();
        exit(EXIT_FAILURE);
    }
}