#ifndef LOG_H
#define LOG_H

#include "Common.h"

#define LOGFILE_NAME    "ux0:/data/Gran/log"

void Log(const char *);
int Logf(const char *, ...);

#endif // LOG_H
