#include "../header/guid_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "../header/types.h"
#include "../header/generation_helper.h"
#include "../header/history_cmd.h"

char** generate_guid_v7(int number)
{
    char **guids = malloc(number * sizeof(char*));
    check_memory_allocation(guids);
    
    srandom(time(NULL));

    for(int i = 0; i < number; i++)
    {
        guids[i] = malloc(37 * sizeof(char)); // GUIDs are 36 characters + null terminator
        check_memory_allocation(guids[i]);
        
        uint64_t  r = rand64();
        uint64_t  tx = get_current_timestamp_MS();
        uint8_t uuid[16];
         
        uuid[0] = (tx >>40) & 0xFF;
        uuid[1] = (tx >>32) & 0xFF;
        uuid[2] = (tx >>24) & 0xFF;
        uuid[3] = (tx >>16) & 0xFF;
        uuid[4] = (tx >>8) & 0xFF;
        uuid[5] = tx & 0xFF;

        //version 7
        uuid[6] = ((r >>56) & 0x0F) | 0x70;
        uuid[7] = (r >>48) & 0xFF;

        //variant: RFC 4122 -> 10xxxxxx
        uuid[8] = ((r >>40) & 0x3F) | 0x80;

        uuid[9] = (r >>32) & 0xFF;
        uuid[10] = (r >>24) & 0xFF;
        uuid[11] = (r >>16) & 0xFF;
        uuid[12] = (r >>8) & 0xFF;
        uuid[13] = r & 0xFF;

        r = rand64();
        uuid[14] = (r >>8) & 0xFF;
        uuid[15] = r & 0xFF;

        sprintf(guids[i],
                 "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                 uuid[0], uuid[1], uuid[2], uuid[3],
                 uuid[4], uuid[5],
                 uuid[6], uuid[7],
                 uuid[8], uuid[9],
                 uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
    }

    history_add(GUIDV7, guids, number);
    return guids;
}

char** generate_guid_v4(int number)
{
    char **guids = malloc(number * sizeof(char*));
    check_memory_allocation(guids);

    srandom(time(NULL)); 

    for(int i = 0; i < number; i++)
    {
        guids[i] = malloc(37 * sizeof(char)); 
        check_memory_allocation(guids[i]);

        uint64_t  r = rand64();
        uint8_t uuid[16];
         
        uuid[0] = (r >>56) & 0xFF;
        uuid[1] = (r >>48) & 0xFF;
        uuid[2] = (r >>40) & 0xFF;
        uuid[3] = (r >>32) & 0xFF;
        uuid[4] = (r >>24) & 0xFF;
        uuid[5] = (r >>16) & 0xFF;

        //version 4
        uuid[6] = ((r >>8) & 0x0F) | 0x40;
        uuid[7] = r & 0xFF;

        r = rand64();
        //variant: RFC 4122 -> 10xxxxxx
        uuid[8] = ((r >>56) & 0x3F) | 0x80;

        uuid[9] = (r >>48) & 0xFF;
        uuid[10] = (r >>40) & 0xFF;
        uuid[11] = (r >>32) & 0xFF;
        uuid[12] = (r >>24) & 0xFF;
        uuid[13] = (r >>16) & 0xFF;
        uuid[14] = (r >>8) & 0xFF;
        uuid[15] = r & 0xFF;

        sprintf(guids[i],
                 "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                 uuid[0], uuid[1], uuid[2], uuid[3],
                 uuid[4], uuid[5],
                 uuid[6], uuid[7],
                 uuid[8], uuid[9],
                 uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
    }
    
    history_add(GUIDV4, guids, number);

    return guids;
}

int get_guid_version(const char* guid)
{
    return atoi((char[]){guid[14], '\0'});
}

GuidVariant check_guid_variant(const char* guid)
{
    char c = tolower(guid[19]);  // first hex digit of the 9th byte

    if (c == '8' || c == '9' || c == 'a' || c == 'b') 
    {
        return RFC4122;
    } 
    else if (c == 'c' || c == 'd') 
    {
        return MICROSOFT;
    } 
    else if (c == 'e' || c == 'f') 
    {
        return FUTURE;
    } 
    else 
    {
        return NCS;
    }
}

void print_generated_guids(char **guids, int version, int count)
{
    
    printf("Generated %d GUID(s) (Version %d):\n", count, version);

    for (int i = 0; i < count; i++) 
    {
        printf("%d. %s\n",i+1, guids[i]);
        free(guids[i]);
    }

    free(guids);
}

bool is_valid_guid_format(const char* guid)
{
    
    const size_t guid_len = 36;
    if (guid == NULL || strlen(guid) != guid_len) 
    {
        return false;
    }

    const char guid_seperator = '-';

    for (int i = 0; i < guid_len; i++) 
    {
        if (guid[i] != guid_seperator && !isxdigit(guid[i])) 
        {
            return false;
        }
    }

    return true;
}
