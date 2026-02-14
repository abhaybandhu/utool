#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include "../header/generation_helper.h"

// This is the SplitMix64 "Finalizer"
// It ensures high avalanche effect (one bit change flips 50% of output)
uint64_t scramble(uint64_t x) 
{
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
    x = (x ^ (x >> 31));
    return x;
}

uint64_t get_current_timestamp_MS() 
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000ULL) + tv.tv_usec;
}

uint64_t rand64()
{
    uint64_t raw = (((uint64_t)random()) << 32) | ((uint64_t)random());
    
    // Scramble them to destroy patterns
    return scramble(raw);
}

void check_memory_allocation(void *ptr)
{
    if (ptr == NULL) 
    {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
}
