#include "../header/utils.h"
#include <stdio.h>
#include <stdlib.h>

#if __APPLE__
    #include <stdlib.h>
#elif defined(__linux__)
    #include <stdlib.h>
#elif defined(_WIN32)
    #include <windows.h>
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