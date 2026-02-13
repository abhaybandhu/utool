#include "../header/history_cmd.h"
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>


// PRIVATE METHODS
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

void history_save(HistoryEntry history_entries,char ** results, int count)
{
    
    FILE *fp = fopen(HISTORY_LOG_FILE, "ab");

    if (fp == NULL) 
    {
        perror("Failed to open history log");
        return;
    }
    
    for (size_t i = 0; i < count; i++) 
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
            localtime_r(&entry.timestamp.tv_sec, &tm);
            strftime(time_buf, sizeof(time_buf), "%d/%m/%Y %H:%M:%S", &tm);

            printf("ID: %lu, Type: %s, Timestamp: %s.%04ld, Result: %s\n",
                   id, CmdTypeName(entry.type),
                   time_buf, entry.timestamp.tv_usec / 1000, entry.result == NULL?  "NULL": entry.result);
        }
    }

    fclose(fp);
}
