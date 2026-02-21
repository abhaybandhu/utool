#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "../header/ulid_cmd.h"
#include "../header/types.h"
#include "../header/generation_helper.h"
#include "../header/history_cmd.h"
#include "../header/utils.h"

const char* ALPHABET = "0123456789ABCDEFGHJKMNPQRSTVWXYZ"; //base 30

void ulid_to_string(const uint8_t bytes[16], char* out) 
{
    // 10 characters for the 48-bit timestamp
    out[0] = ALPHABET[(bytes[0] & 0xE0) >> 5];
    out[1] = ALPHABET[bytes[0] & 0x1F];
    out[2] = ALPHABET[(bytes[1] & 0xF8) >> 3];
    out[3] = ALPHABET[((bytes[1] & 0x07) << 2) | ((bytes[2] & 0xC0) >> 6)];
    out[4] = ALPHABET[(bytes[2] & 0x3E) >> 1];
    out[5] = ALPHABET[((bytes[2] & 0x01) << 4) | ((bytes[3] & 0xF0) >> 4)];
    out[6] = ALPHABET[((bytes[3] & 0x0F) << 1) | ((bytes[4] & 0x80) >> 7)];
    out[7] = ALPHABET[(bytes[4] & 0x7C) >> 2];
    out[8] = ALPHABET[((bytes[4] & 0x03) << 3) | ((bytes[5] & 0xE0) >> 5)];
    out[9] = ALPHABET[bytes[5] & 0x1F];

    // 16 characters for the 80-bit randomness
    out[10] = ALPHABET[(bytes[6] & 0xF8) >> 3];
    out[11] = ALPHABET[((bytes[6] & 0x07) << 2) | ((bytes[7] & 0xC0) >> 6)];
    out[12] = ALPHABET[(bytes[7] & 0x3E) >> 1];
    out[13] = ALPHABET[((bytes[7] & 0x01) << 4) | ((bytes[8] & 0xF0) >> 4)];
    out[14] = ALPHABET[((bytes[8] & 0x0F) << 1) | ((bytes[9] & 0x80) >> 7)];
    out[15] = ALPHABET[(bytes[9] & 0x7C) >> 2];
    out[16] = ALPHABET[((bytes[9] & 0x03) << 3) | ((bytes[10] & 0xE0) >> 5)];
    out[17] = ALPHABET[bytes[10] & 0x1F];
    out[18] = ALPHABET[(bytes[11] & 0xF8) >> 3];
    out[19] = ALPHABET[((bytes[11] & 0x07) << 2) | ((bytes[12] & 0xC0) >> 6)];
    out[20] = ALPHABET[(bytes[12] & 0x3E) >> 1];
    out[21] = ALPHABET[((bytes[12] & 0x01) << 4) | ((bytes[13] & 0xF0) >> 4)];
    out[22] = ALPHABET[((bytes[13] & 0x0F) << 1) | ((bytes[14] & 0x80) >> 7)];
    out[23] = ALPHABET[(bytes[14] & 0x7C) >> 2];
    out[24] = ALPHABET[((bytes[14] & 0x03) << 3) | ((bytes[15] & 0xE0) >> 5)];
    out[25] = ALPHABET[bytes[15] & 0x1F];

    out[26] = '\0'; // Null terminator
}

char ** generate_ulid_cmd(size_t number)
{
    // Placeholder for ULID generation logic
    char **ulids = malloc(number * sizeof(char*));
    check_memory_allocation(ulids);

    init_random();
    
    for (size_t i = 0; i < number; i++) 
    {
        ulids[i] = malloc(27 * sizeof(char)); // ULIDs are 26 characters + null terminator
        check_memory_allocation(ulids[i]);

        // 48 bits used for timestamp, 80 bits for randomness

        uint8_t ulid[16];
        uint64_t now = get_current_timestamp_MS(); 
        ulid[0] = (now >> 40) & 0xFF;
        ulid[1] = (now >> 32) & 0xFF;
        ulid[2] = (now >> 24) & 0xFF;
        ulid[3] = (now >> 16) & 0xFF;
        ulid[4] = (now >> 8) & 0xFF;
        ulid[5] = now & 0xFF;

        uint64_t  r = rand64();
        ulid[6] = (r >> 56) & 0xFF;
        ulid[7] = (r >> 48) & 0xFF;
        ulid[8] = (r >> 40) & 0xFF;
        ulid[9] = (r >> 32) & 0xFF;
        ulid[10] = (r >> 24) & 0xFF;
        ulid[11] = (r >> 16) & 0xFF;
        ulid[12] = (r >> 8) & 0xFF;
        ulid[13] = r & 0xFF;

        r = rand64();
        ulid[14] = (r >> 8) & 0xFF;
        ulid[15] = r & 0xFF;

        ulid_to_string(ulid, ulids[i]);
    }

    history_add(ULID, ulids, number);
    return ulids;
}