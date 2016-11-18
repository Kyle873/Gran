#include "Input.h"

SceCtrlData pad;

int pressedButtons;
int currentButtons;

bool Input_HoldButtons(uint32_t buttons)
{
    if ((pad.buttons & buttons) == buttons)
    {
        uint64_t timeStart = sceKernelGetProcessTimeWide();
        
        while ((pad.buttons & buttons) == buttons)
        {
            sceKernelDelayThread(10 * 1000);
            sceCtrlReadBufferPositiveExt2(0, &pad, 1);
            
            pressedButtons = pad.buttons & ~currentButtons;
            currentButtons = pad.buttons;
            
            if ((sceKernelGetProcessTimeWide() - timeStart) > INPUT_LONG_PRESS_TIME)
                return true;
        }
    }
    
    return false;
}

void Input_Update()
{
    memset(&pad, 0, sizeof(SceCtrlData));
    sceCtrlReadBufferPositiveExt2(0, &pad, 1);
    
    pressedButtons = pad.buttons & ~currentButtons;
    currentButtons = pad.buttons;
}
