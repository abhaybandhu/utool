#include <time.h>
void init_random();
int platform_localtime(time_t *timep, struct tm *result);
int ensure_directory(const char *path);