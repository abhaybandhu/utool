#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../header/config_cmd.h"
#include "../header/copy_cmd.h"

#ifdef _WIN32
    #include <windows.h>
#endif


#ifdef __linux__
    int command_exists(const char *cmd)
    {
        char buffer[256];
        snprintf(buffer, sizeof(buffer),
                "command -v %s >/dev/null 2>&1", cmd);

        return system(buffer) == 0;
    }

    int has_wl_copy() { return command_exists("wl-copy"); }
    int has_xclip()   { return command_exists("xclip"); }
    int has_xsel()    { return command_exists("xsel"); }
    
    bool hasclipboard_utility() 
    {
        return has_wl_copy() || has_xclip() || has_xsel();
    }
#endif

void copy_to_clipboard(const char *text)
{
    bool is_copy_enabled = getCopyConfig();
    if (!is_copy_enabled) 
    {
        return;
    }
#ifdef _WIN32
    const size_t len = strlen(text) + 1;

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), text, len);
    GlobalUnlock(hMem);

    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

#elif __APPLE__
    FILE *pipe = popen("pbcopy", "w");
    if (pipe) 
    {
        fputs(text, pipe);
        pclose(pipe);
    }

#elif __linux__
    if (!hasclipboard_utility())
    {
        fprintf(stderr, "No clipboard utility found. Please install wl-copy, xclip, or xsel.\n");
        return;
    }

    FILE *pipe = popen("wl-copy 2>/dev/null || xclip -selection clipboard", "w");
    if (pipe) 
    {
        fputs(text, pipe);
        pclose(pipe);
    }
#endif
}

