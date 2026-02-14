#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "../header/guid_cmd.h"
#include "../header/guid.h"
#include "../header/types.h"

void guid_help() 
{
    printf("Usage: %s guid [options]\n",CLI_NAME);
    printf("\t-v, --version 4|7   GUID version (default 7)\n");
    printf("\t-n, --count NUM     Number of GUIDs\n");
    printf("\t-c, --check <guid>  Check if provided guid valid\n");
}

void print_variant (GuidVariant variant) 
{
    printf(" 2.\t");
    switch (variant) 
    {
        case NCS:
            printf("Variant: NCS (obsolete)\n");
            break;
        case RFC4122:
            printf("Variant: RFC 4122 (standard GUID/UUID)\n");
            break;
        case MICROSOFT:
            printf("Variant: Microsoft (legacy)\n");
            break;
        case FUTURE:
            printf("Variant: Future / reserved\n");
            break;
        default:
            printf("Variant: Unknown\n");
    }
}
void print_version(const int version, const char* guid)
{
    if(version >= MIN_VERSION && version <= MAX_VERSION)
    {
        printf("The GUID %s :\n 1.\tVersion %d.\n",guid, version);
    } 
    else 
    {
        printf("The GUID %s is of an unknown version.\n", guid);
    }
}

void guid_command(int argc, char *argv[]) 
{
    int opt;
    int count = 1;
    int version = VERSION_7;

    struct option opts[] = 
    {
        {"version", required_argument, NULL, 'v'},
        {"count",   required_argument, NULL, 'n'},
        {"check",   required_argument, NULL, 'c'},
        {"help",    no_argument,       NULL, 'h'},
        {0, 0, 0, 0}
    };

    //Initialise history

    while ((opt = getopt_long(argc, argv, "v:n:c:h", opts, NULL)) != -1) 
    {
        switch (opt) 
        {
            case 'c':
                if (!is_valid_guid_format(optarg)) 
                {
                    printf("The GUID `%s` is not in a valid format.\n", optarg);
                    exit(EXIT_FAILURE);
                }
                print_version(get_guid_version(optarg), optarg);
                print_variant(check_guid_variant(optarg));
                return;
            case 'v':
                version = atoi(optarg);
                break;
            case 'n':
                count = atoi(optarg);
                if (count <= 0) 
                {
                    printf("Invalid count: %d. Count must be a positive integer.\n", count);
                    exit(EXIT_FAILURE);
                }
                else if (count > MAXCOUNT) 
                {
                    printf("Count too large: %d. Please specify a count of 1000 or less.\n", count);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                guid_help();
                return;
        }
    }

    char **guids = NULL;

    switch (version) 
    {
        case VERSION_4:
            guids = generate_guid_v4(count);
            break;
        case VERSION_7:
            guids = generate_guid_v7(count);
            break;
        default:
            printf("Unsupported GUID version: %d. Supported versions are 4 and 7.\n", version);
            exit (EXIT_FAILURE);
    }


    print_generated_guids(guids, version, count);
}

