#include "Log.h"

void Log(const char *text)
{
    int f = sceIoOpen(LOGFILE_NAME, SCE_O_WRONLY | SCE_O_APPEND | SCE_O_CREAT, 0777);
    
    sceIoWrite(f, text, strlen(text));
    
    sceIoClose(f);
}

int Logf(const char *format, ...)
{
    char buffer[1024];
    int f = sceIoOpen(LOGFILE_NAME, SCE_O_WRONLY | SCE_O_APPEND | SCE_O_CREAT, 0777);
    
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    sceIoWrite(f, buffer, strlen(buffer));
    
    sceIoClose(f);
    
    return ret;
}
