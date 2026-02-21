#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include "../header/generation_helper.h"
#include "../header/utils.h"
    
#ifdef WIN32
    #include <windows.h>
    #include <bcrypt.h>
    #ifdef _MSC_VER
        #pragma comment(lib, "bcrypt.lib")  // only for MSVC
    #endif
#elif defined(__linux__)
    #include <sys/random.h>
#endif

uint64_t get_current_timestamp_MS() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000ULL) + tv.tv_usec;
}

uint64_t rand64()
{
    #ifdef _WIN32
        uint64_t value;
        if (BCryptGenRandom(NULL, (PUCHAR)&value, sizeof(value), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) 
        {
            fprintf(stderr, "Failed to generate random number\n");
            exit(EXIT_FAILURE);
        }
        return value;
    #elif defined(__linux__)
        uint64_t value;
        int result = getrandom(&value, sizeof(value), 0);
        if (result != sizeof(value)) {
            fprintf(stderr, "Failed to generate random number\n");
            exit(EXIT_FAILURE);
        }
        return value;
    #elif defined(__APPLE__)
        uint64_t value;
        arc4random_buf(&value, sizeof(value)); // preferred over combining arc4random()
        return value;
    #else
        #error "Unsupported platform. Please report this issue to the developer."
    #endif
}

void check_memory_allocation(void *ptr)
{
    if (ptr == NULL) 
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}
