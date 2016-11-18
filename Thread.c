#include "Thread.h"

/*
 * Tricky way to freeze main thread, we set our plugin priority to 0 (max)
 * and we start two threads with 0 priority in order to get VITA scheduler
 * to always reschedule our threads instead of main one
 */

volatile bool unpaused = false;

void Thread_PauseMainThread()
{
    sceKernelChangeThreadPriority(0, 0);
    
    unpaused = false;
    
    for (int i = 0; i < 2; i++)
    {
        SceUID stubUID = sceKernelCreateThread("Gran Stub Thread", Thread_StubThread, 0x00, 0x10000, 0, 0, NULL);
        
        if (stubUID >= 0)
            sceKernelStartThread(stubUID, 0, NULL);
    }
}

void Thread_ResumeMainThread()
{
    unpaused = true;
    
    sceKernelChangeThreadPriority(0, 64);
}

int Thread_StubThread(SceSize args, void *argp)
{
    while (true)
        if (unpaused)
            sceKernelExitDeleteThread(0);
}
