#include <stdbool.h>
char** generate_guid_v7(int number);
char** generate_guid_v4(int number);
void check_guid_version(const char* guid);
void check_guid_variant(const char* guid);
void print_generated_guids(char **guids,int version, int count);
bool is_valid_guid_format(const char* guid);