#include <sys/time.h>
#include "types.h"
#include <string.h>

#ifndef HISTORY_H
#define HISTORY_H
    #define HISTORY_LOG_FILE BIN_DIR "/" CLI_NAME "History.log"

    typedef struct 
    {
        CmdType type;
        char result[36];
        struct timeval timestamp;
    } HistoryEntry;

#endif

void history_add(CmdType command_type,char ** results,int count);
void history_show(CmdType filter_type);