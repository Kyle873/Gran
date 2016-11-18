#ifndef THREAD_H
#define THREAD_H

#include "Common.h"

void Thread_PauseMainThread();
void Thread_ResumeMainThread();

int Thread_StubThread(SceSize, void *);

#endif // THREAD_H
