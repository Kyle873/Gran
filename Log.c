#include "Log.h"

void Log(const char *text)
{
    FILE *f = fopen(LOGFILE_NAME, "a");
    
	fwrite(text, strlen(text), 1, f);
	
	fclose(f);
}

int Logf(const char *format, ...)
{
    char buffer[1024];
    FILE *f = fopen(LOGFILE_NAME, "a");
    
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
	fwrite(buffer, strlen(buffer), 1, f);
	
	fclose(f);
    
    return ret;
}
