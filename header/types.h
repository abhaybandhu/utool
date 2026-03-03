#ifndef TYPES_H
#define TYPES_H
    #define MAXCOUNT 1000
    #define CLI_NAME "utool"
    #define BIN_DIR ".bin"
    
    typedef enum
    {
        UNKNOWN =0,
        ALL =1,
        GUIDV4=2,
        GUIDV7=3,
        ULID=4
    } CmdType;

    typedef enum 
    {
        MIN_VERSION = 1,
        MAX_VERSION = 8,
        VERSION_4 = 4,
        VERSION_7 = 7,
    } GuidVersion;


    typedef enum 
    {
        NCS = 0,
        RFC4122 = 1,
        MICROSOFT = 2,
        FUTURE = 3,
        INVALID = -1
    } GuidVariant;

#endif