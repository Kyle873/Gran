#include "Common.h"
#include "Menu.h"

int Main_Thread(SceSize args, void *argp)
{
    CSV_Parse_ItemNames();
    CSV_Parse_ItemTypes();
    CSV_Parse_ItemCategories();
    
    Menu_Init();
    
    while (true)
    {
        Draw_Init();
        
        Input_Update();
        Menu_Update();
    }
    
    return 0;
}

int _start(SceSize args, void *argp)
{
    SceUID mainThreadUID = sceKernelCreateThread("Gran Main Thread", Main_Thread, 0x40, 0x40000, 0, 0, NULL);
    
    if (mainThreadUID >= 0)
        sceKernelStartThread(mainThreadUID, 0, NULL);
    
    return 0;
}
