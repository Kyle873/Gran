#ifndef MENU_H
#define MENU_H

#include "Common.h"
#include "Thread.h"
#include "Input.h"
#include "Draw.h"
#include "Memory.h"
#include "Nova.h"
#include "CSV.h"

#define MENU_WIDTH                  (SCREEN_WIDTH / 4)
#define MENU_HEIGHT                 ((SCREEN_HEIGHT / 2) - 56)
#define MENU_X                      ((SCREEN_WIDTH / 2) - (MENU_WIDTH / 2))
#define MENU_Y                      ((SCREEN_HEIGHT / 2) - (MENU_HEIGHT / 2))

#define MENU_MAX_ENTRIES            (20)
#define MENU_MAX_OPTIONS            (8)

#define MENU_STRING_SIZE            (64)

#define GenDataEntryPtr(page, n)    &menuEntries[MENU_PAGE_##page][MENU_##page##_DATA + n]

enum
{
    MENU_COLOR_BACK = 0xC0241E10,
    MENU_COLOR_BORDER = 0xC06B644E,
    MENU_COLOR_TEXT = COLOR_WHITE,
    MENU_COLOR_SELECT = COLOR_CYAN,
    MENU_COLOR_FREEZE = COLOR_YELLOW,
    MENU_COLOR_SELECTFREEZE = COLOR_MAGENTA,
};

enum
{
    MENU_PAGE_MAIN,
    MENU_PAGE_PLAYER,
    MENU_PAGE_ITEMEDIT,
    MENU_PAGE_SETTINGS,
    
    MENU_PAGE_MAX,
};

enum
{
    MENU_ENTRY_ACTION,
    MENU_ENTRY_NUMERIC,
    MENU_ENTRY_SEPERATOR,
};

enum
{
    MENU_ITEMEDIT_SLOT,
    MENU_ITEMEDIT_GUID = 2,
    MENU_ITEMEDIT_TYPE,
    MENU_ITEMEDIT_CATEGORY,
    MENU_ITEMEDIT_ID,
    MENU_ITEMEDIT_DATA = 7,
};

typedef void (*MenuSelect)();
typedef void (*MenuUpdate)();
typedef void (*MenuChange)();

typedef struct
{
    const char *name;
    char *prefix;
    char *suffix;
    int type;
    
    int dataType;
    uint32_t address;
    int32_t value;
    
    int min;
    int max;
    int increment;
    bool hex;
    
    bool freezable;
    bool frozen;
    
    MenuSelect select;
    MenuSelect update;
    MenuChange change;
} MenuEntry;

struct
{
    bool open;
    
    int index[MENU_PAGE_MAX];
    int page;
    size_t size;
    int increment;
    
    int itemSlot;
    Item item;
    bool storage;
} menu;

void Menu_Init();
void Menu_Toggle();
void Menu_Input();
void Menu_Draw();
void Menu_Update();

void Menu_SetSize();

void Menu_DrawBack();
void Menu_DrawTitle();
void Menu_DrawEntries();

void Menu_UpdateValues();
void Menu_UpdateFrozenValues();

void Menu_Main_Select();

void Menu_Player_Update();

void Menu_ItemEdit_Update();
void Menu_ItemEdit_Slot_Change();

void Menu_Settings_MemoryOffset_Update();
void Menu_Settings_MemoryOffset_Change();

#endif // MENU_H
