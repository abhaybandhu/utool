#include "../header/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if _WIN32
    #include <windows.h>
     #include <direct.h>   // _mkdir
    #define MKDIR(path) _mkdir(path)
#else
    #include <stdlib.h>
    #include <sys/stat.h> // mkdir
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0755)
#endif

void init_random() 
{

#ifdef __linux__
    srandom(time(NULL));
#elif defined(_WIN32)
    srand(time(NULL));
#endif

}


int platform_localtime(time_t *timep, struct tm *result) 
{
    #ifdef _WIN32
        return localtime_s(result, timep);
    #else
        return localtime_r(timep, result) == NULL ? -1 : 0;
    #endif
}

int ensure_directory(const char *path)
{
    if (MKDIR(path) == 0)
        return 0;  // created successfully

    if (errno == EEXIST)
        return 0;  // already exists (this is fine)

    return -1;     // real error
}