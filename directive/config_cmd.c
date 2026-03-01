#include <stdbool.h>
#include "../header/utils.h"
#include "../header/types.h"
#include "../header/config_cmd.h"
#include <stdio.h>
#include <stdlib.h>

#define CONFIG_FILE BIN_DIR "/config.bin"

typedef struct 
{
    bool enable_copy;
} Config;

// PRIVATE METHODS
Config* load_config() 
{
    FILE *file = fopen(CONFIG_FILE, "rb");
    if (file) 
    {
        Config *config = malloc(sizeof(Config));
        if (!config) 
        {
            perror("Failed to allocate memory for config");
            fclose(file);
            return NULL;
        }

        fread(config, sizeof(Config), 1, file);
        fclose(file);
        return config;
    }
    else
    {
        //perror("Failed to load config");
        return NULL;
    }
}

void save_config(Config *config) 
{
    if (ensure_directory(BIN_DIR) != 0) 
    {
        perror("Failed to create config directory");
        return;
    }

    FILE *file = fopen(CONFIG_FILE, "wb");
    if (file) 
    {
        fwrite(config, sizeof(Config), 1, file);
        fclose(file);
    }
    else
    {
        perror("Failed to save config");
    }
}

void setDefaultConfig(bool enable_copy) 
{
    Config *config = malloc(sizeof(Config));
    if (config == NULL) 
    {
        perror("Failed to allocate memory for config");
        return;
    }

    config->enable_copy = enable_copy;
    save_config(config);
    free(config);
}

bool getCopyConfig()
{
    Config *config = load_config();
    if (config != NULL) 
    {
        bool enable_copy = config->enable_copy;
        free(config);
        return enable_copy;
    }
    else
    {
        // If config loading fails, default to true
        return true;
    }
}
