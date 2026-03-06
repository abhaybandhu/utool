#include "../header/history_cmd.h"
#include "../header/copy_cmd.h"
#include "../header/utils.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


// PRIVATE METHODS
int getTypeLength(CmdType type)
{
    switch (type) 
    {
        case GUIDV4:
        case GUIDV7:
            return 36;
        case ULID:
            return 26;
        default:
            return 0;
    }
}
char* CmdTypeName(CmdType type)
{
    switch (type) {
        case GUIDV4:
            return "GUIDV4";
        case GUIDV7:
            return "GUIDV7";
        case ULID:
            return "ULID";
        default:
            return "UNKNOWN";
    }
}

const char* result_to_str(char ** result, int count, int length)
{
    int total_length = (length * count)+ (count - 1) *2 + 1; // length of result + ", " between results + null terminator
    char * result_str = (char *)calloc(1,total_length);

    if (!result_str)    {
        perror("Failed to allocate memory for result string");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; ++i) 
    {
        strcat(result_str, result[i]);
        if (i < count - 1) 
        {
            strcat(result_str, ", ");
        }
    }

    strcat(result_str, "\0"); // Null terminator

    return result_str;
}

void history_save(HistoryEntry history_entries,char ** results, int count)
{
    if (ensure_directory(BIN_DIR) != 0) 
    {
        perror("Failed to create history log directory");
        return;
    }
    
    FILE *fp = fopen(HISTORY_LOG_FILE, "ab");

    if (fp == NULL) 
    {
        perror("Failed to open history log");
        return;
    }
    
    for (int i = 0; i < count; i++) 
    {
        snprintf(history_entries.result, sizeof(history_entries.result), "%s", results[i]);
        fwrite(&history_entries, sizeof(history_entries), 1, fp);
    }
    
    fclose(fp);
}


void history_add(CmdType command_type,char ** results,int count)
{
    HistoryEntry history_entries;
    
    history_entries.type = command_type;    

    //Get time of entry
    struct timeval timestamp;
    gettimeofday(&timestamp, NULL);
    history_entries.timestamp = timestamp;
    memset(&history_entries.result, 0, sizeof(history_entries.result));

    history_save(history_entries, results, count);

    //copy to clipboard
    int length = getTypeLength(command_type);
    const char * result_str = result_to_str(results, count,length);
    copy_to_clipboard(result_str);

    free((void*)result_str);
}


void history_show(CmdType filter_type)
{
    FILE *fp = fopen(HISTORY_LOG_FILE, "rb");

    if (fp == NULL) 
    {
        perror("Failed to open history log");
        return;
    }

    HistoryEntry entry;
    long id = 0;
    char time_buf[32];
    struct tm tm;

    while (fread(&entry, sizeof(HistoryEntry), 1, fp) == 1) 
    {
        ++id;
        if (filter_type == ALL || entry.type == filter_type) 
        {
            printf("Raw tv_sec: %lld\n", (long long)entry.timestamp.tv_sec);
            time_t raw_time = (time_t)entry.timestamp.tv_sec;
            if (platform_localtime(&raw_time, &tm) != 0) 
            {
                // If raw_time is -1 or very large, Windows will fail here
                fprintf(stderr, "Failed to convert timestamp: %lld\n", (long long)raw_time);
                perror("Error detail");
                fclose(fp);
                exit(EXIT_FAILURE);
            }

            strftime(time_buf, sizeof(time_buf), "%d/%m/%Y %H:%M:%S", &tm);

            printf("ID: %lu, Type: %s, Timestamp: %s.%04ld, Result: %s\n",
                   id, CmdTypeName(entry.type),
                   time_buf, entry.timestamp.tv_usec / 1000, entry.result);
        }
    }

    fclose(fp);
}

/*
If you are reading from a binary file, ensure your struct uses fixed-width types (like int64_t) instead of time_t, as time_t changes size between platforms.
*/
