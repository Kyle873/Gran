#include "Menu.h"

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

MenuEntry menuEntries[][MENU_MAX_ENTRIES] =
{
    // Main Menu
    {
        {
            .name = "Player",
            .select = Menu_Main_Select,
        },
        {
            .name = "Inventory/Storage",
            .select = Menu_Main_Select,
        },
        /*
        {
            .name = "Settings",
            .select = Menu_Main_Select,
        },
        */
    },
    
    // Player
    {
        {
            .name = "Level",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_LEVEL,
            .min = 1,
            .max = 200,
        },
        {
            .name = "EXP",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_EXP,
            .min = 0,
            .max = 1000000000,
        },
        {
            .type = MENU_ENTRY_SEPERATOR,
        },
        {
            .name = "Gran Energy",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_GRANENERGY,
            .min = 0,
            .max = 100000000,
            .freezable = true,
        },
        {
            .type = MENU_ENTRY_SEPERATOR,
        },
        {
            .name = "Current HP",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_CURRENTHP,
            .min = 0,
            .max = 9999,
            .freezable = true,
        },
        {
            .name = "Max HP",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_MAXHP,
            .min = 0,
            .max = 9999,
        },
        {
            .name = "Current GP",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_CURRENTGP,
            .min = 0,
            .max = 999,
            .freezable = true,
        },
        {
            .name = "Max GP",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .address = ADDR_MAXGP,
            .min = 0,
            .max = 999,
        },
    },
    
    // Item Editor
    {
        {
            .name = "Slot",
            .type = MENU_ENTRY_NUMERIC,
            .value = 1,
            .min = 1,
            .max = MAX_INV_ENTRIES,
            .change = Menu_ItemEdit_Slot_Change,
        },
        {
            .type = MENU_ENTRY_SEPERATOR,
        },
        {
            .name = "GUID",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .min = 0,
            .max = 1000000000,
        },
        {
            .name = "Type",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_SHORT,
            .min = 0,
            .max = MAX_ITEM_TYPES - 1,
        },
        {
            .name = "Category",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_INT,
            .min = 0,
            .max = 0,
        },
        {
            .name = "ID",
            .type = MENU_ENTRY_NUMERIC,
            .dataType = MEMORY_SHORT,
            .min = 0,
            .max = 9999,
        },
        {
            .type = MENU_ENTRY_SEPERATOR,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
        {
            .name = "",
            .type = MENU_ENTRY_NUMERIC,
        },
    },
    
    /* Settings
    {
    },
    */
};

void Menu_Init()
{
    menu.increment = 1;
    menu.itemSlot = 1;
    
    Menu_SetSize();
}

void Menu_Toggle()
{
    menu.open = !menu.open;
    
    if (menu.open)
    {
        Thread_PauseMainThread();
        sceCtrlSetButtonIntercept(true);
    }
    else
    {
        Thread_ResumeMainThread();
        sceCtrlSetButtonIntercept(false);
    }
}

void Menu_Input()
{
    MenuEntry *entry = Menu_GetEntry();
    bool modified = false;
    
    if (pressedButtons == SCE_CTRL_UP)
    {
        if (menu.index[menu.page] - 1 < 0)
            menu.index[menu.page] = menu.size - 1;
        else
            menu.index[menu.page]--;
        
        while (menuEntries[menu.page][menu.index[menu.page]].type == MENU_ENTRY_SEPERATOR)
            menu.index[menu.page]--;
    }
    if (pressedButtons == SCE_CTRL_DOWN)
    {
        if (menu.index[menu.page] + 1 >= menu.size)
            menu.index[menu.page] = 0;
        else
            menu.index[menu.page]++;
        
        while (menuEntries[menu.page][menu.index[menu.page]].type == MENU_ENTRY_SEPERATOR)
            menu.index[menu.page]++;
    }
    
    if (entry->type != MENU_ENTRY_ACTION && entry->type != MENU_ENTRY_SEPERATOR)
    {
        if (pressedButtons == SCE_CTRL_LEFT)
        {
            if (entry->increment != 0)
            {
                if (entry->value - entry->increment < entry->min)
                    entry->value = entry->min;
                else
                    entry->value -= entry->increment;
            }
            else
            {
                if (entry->value - menu.increment < entry->min)
                    entry->value = entry->min;
                else
                    entry->value -= menu.increment;
            }
            
            if (entry->change)
                entry->change();
            
            modified = true;
        }
        if (pressedButtons == SCE_CTRL_RIGHT)
        {
            if (entry->increment != 0)
            {
                if (entry->value + entry->increment > entry->max)
                    entry->value = entry->max;
                else
                    entry->value += entry->increment;
            }
            else
            {
                if (entry->value + menu.increment > entry->max)
                    entry->value = entry->max;
                else
                    entry->value += menu.increment;
            }
            
            if (entry->change)
                entry->change();
            
            modified = true;
        }
    }
    
    if (menu.page != MENU_PAGE_MAIN)
    {
        if (pressedButtons == SCE_CTRL_L1 && menu.increment > 1)
            menu.increment /= 10;
        if (pressedButtons == SCE_CTRL_R1 && menu.increment < 1000000000)
            menu.increment *= 10;
    }
        
    if (pressedButtons == SCE_CTRL_CROSS)
    {
        switch (menu.page)
        {
        case MENU_PAGE_PLAYER:
        case MENU_PAGE_ITEMEDIT:
        case MENU_PAGE_SETTINGS:
            menu.page = MENU_PAGE_MAIN;
            Menu_SetSize();
            break;
        }
    }
    
    if (pressedButtons == SCE_CTRL_CIRCLE && entry->select)
        entry->select();

    if (pressedButtons == SCE_CTRL_SQUARE && menu.page == MENU_PAGE_ITEMEDIT)
    {
        MenuEntry *slot = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_SLOT];
        
        menu.storage = !menu.storage;
        
        slot->value = 1;
        slot->change();
        
        if (menu.storage)
            slot->max = MAX_STORAGE_ENTRIES;
        else
            slot->max = MAX_INV_ENTRIES;
    }
        
    if (pressedButtons == SCE_CTRL_TRIANGLE && entry->freezable)
        entry->frozen = !entry->frozen;
    
    if (modified && !entry->change)
    {
        switch (entry->dataType)
        {
        case MEMORY_BYTE:
            Memory_WriteByte(entry->address, entry->value);
            break;
        case MEMORY_SHORT:
            Memory_WriteShort(entry->address, entry->value);
            break;
        case MEMORY_INT:
            Memory_WriteInt(entry->address, entry->value);
            break;
        }
    }
}

void Menu_Draw()
{
    Menu_DrawBack();
    Menu_DrawTitle();
    Menu_DrawEntries();
}

void Menu_Update()
{
    if ((!menu.open && Input_HoldButtons(SCE_CTRL_SELECT)) || (menu.open && pressedButtons & SCE_CTRL_SELECT))
        Menu_Toggle();
    
    Menu_UpdateFrozenValues();
    
    if (menu.open)
    {
        Menu_UpdateValues();
        Menu_Input();
        Menu_Draw();
        
        if (menu.page == MENU_PAGE_ITEMEDIT)
            Menu_ItemEdit_Update();
    }
}

void Menu_SetSize()
{
    menu.size = 0;
    
    while (menuEntries[menu.page][menu.size].name != NULL || menuEntries[menu.page][menu.size].type == MENU_ENTRY_SEPERATOR)
        menu.size++;
}

void Menu_DrawBack()
{
    Draw_SetPosition(MENU_X, MENU_Y);
    
    Draw_SetFGColor(MENU_COLOR_BACK);
    Draw_RectangleFill(MENU_WIDTH, MENU_HEIGHT);
    
    Draw_SetFGColor(MENU_COLOR_BORDER);
    Draw_Rectangle(MENU_WIDTH, MENU_HEIGHT);
}

void Menu_DrawTitle()
{
    Draw_SetFGColor(COLOR_WHITE);
    Draw_SetBGColor(MENU_COLOR_BACK);
    
    Draw_SetPosition(MENU_X + 8, MENU_Y + 8);
    
    switch (menu.page)
    {
    case MENU_PAGE_MAIN:
        Draw_Print("Main Menu");
        break;
    case MENU_PAGE_PLAYER:
        Draw_Print("Player");
        Draw_SetPosition(MENU_X + 8, MENU_Y + 16);
        Draw_Printf("Increment: %d", menu.increment);
        break;
    case MENU_PAGE_ITEMEDIT:
        Draw_Print("Item Editor");
        Draw_SetPosition(MENU_X + 8, MENU_Y + 16);
        Draw_Printf("Increment: %d", menu.increment);
        Draw_SetPosition(MENU_X + 8, MENU_Y + 24);
        if (menu.storage)
            Draw_Printf("Storage");
        else
            Draw_Printf("Inventory");
        break;
    case MENU_PAGE_SETTINGS:
        Draw_Print("Settings");
        break;
    }
}

void Menu_DrawEntries()
{
    Draw_SetBGColor(MENU_COLOR_BACK);
    
    for (int i = 0; i < menu.size; i++)
    {
        MenuEntry *entry = &menuEntries[menu.page][i];
        
        if (entry->name == NULL)
            continue;
        
        float time = sin((float)sceKernelGetProcessTimeWide() / (1000.0f * 250.0f));
        uint32_t color;
        
        if (i == menu.index[menu.page] && entry->frozen)
            color = SetColorGreenByte(MENU_COLOR_SELECTFREEZE, (uint8_t)(128 + (time * 127))) | SetColorBlueByte(MENU_COLOR_SELECTFREEZE, (uint8_t)(128 + (time * 127)));
        else if (i == menu.index[menu.page])
            color = SetColorRedByte(MENU_COLOR_SELECT, (uint8_t)(224 + (time * 31)));
        else if (entry->frozen)
            color = SetColorGreenByte(MENU_COLOR_FREEZE, (uint8_t)(192 + (time * 63)));
        else
            color = MENU_COLOR_TEXT;
        
        Draw_SetFGColor(color);
        Draw_SetPosition(MENU_X + 8, MENU_Y + 48 + (i * SCREEN_GLYPH_H));
        
        Draw_Print(entry->name);
        
        switch (entry->type)
        {
        case MENU_ENTRY_NUMERIC:
            if (entry->hex)
            {
                if (entry->prefix && entry->suffix)
                    Draw_Printf(": %s%X%s", entry->prefix, entry->value, entry->suffix);
                else if (entry->prefix)
                    Draw_Printf(": %s%X", entry->prefix, entry->value);
                else if (entry->suffix)
                    Draw_Printf(": %X%s", entry->value, entry->suffix);
                else
                    Draw_Printf(": %X", entry->value);
            }
            else
            {
                if (entry->prefix && entry->suffix)
                    Draw_Printf(": %s%" PRId32 "%s", entry->prefix, entry->value, entry->suffix);
                else if (entry->prefix)
                    Draw_Printf(": %s%" PRId32, entry->prefix, entry->value);
                else if (entry->suffix)
                    Draw_Printf(": %" PRId32 "%s", entry->value, entry->suffix);
                else
                    Draw_Printf(": %" PRId32, entry->value);
            }
            break;
        }
    }
}

void Menu_UpdateValues()
{
    for (int i = 0; i < menu.size; i++)
    {
        MenuEntry *entry = &menuEntries[menu.page][i];
        
        if (entry->update)
        {
            entry->update();
            continue;
        }
        
        if (entry->address == 0)
            continue;
        
        switch (entry->dataType)
        {
        case MEMORY_BYTE:
            entry->value = Memory_ReadByte(entry->address);
            break;
        case MEMORY_SHORT:
            entry->value = Memory_ReadShort(entry->address);
            break;
        case MEMORY_INT:
            entry->value = Memory_ReadInt(entry->address);
            break;
        }
    }
}

void Menu_UpdateFrozenValues()
{
    for (int i = 0; i < MENU_PAGE_MAX; i++)
        for (int j = 0; j < menu.size; j++)
        {
            MenuEntry *entry = &menuEntries[i][j];
            
            if (!entry->freezable || !entry->frozen)
                continue;
            
            switch (entry->dataType)
            {
            case MEMORY_BYTE:
                Memory_WriteByte(entry->address, entry->value);
                break;
            case MEMORY_SHORT:
                Memory_WriteShort(entry->address, entry->value);
                break;
            case MEMORY_INT:
                Memory_WriteInt(entry->address, entry->value);
                break;
            }
        }
}

void Menu_Main_Select()
{
    menu.page = menu.index[menu.page] + 1;
    
    Menu_SetSize();
}

void Menu_ItemEdit_Update()
{
    MenuEntry *slot = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_SLOT];
    MenuEntry *GUID = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_GUID];
    MenuEntry *type = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_TYPE];
    MenuEntry *category = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_CATEGORY];
    MenuEntry *ID = &menuEntries[MENU_PAGE_ITEMEDIT][MENU_ITEMEDIT_ID];
    MenuEntry *data[] =
    {
        GenDataEntryPtr(ITEMEDIT, 0),
        GenDataEntryPtr(ITEMEDIT, 1),
        GenDataEntryPtr(ITEMEDIT, 2),
        GenDataEntryPtr(ITEMEDIT, 3),
        GenDataEntryPtr(ITEMEDIT, 4),
        GenDataEntryPtr(ITEMEDIT, 5),
        GenDataEntryPtr(ITEMEDIT, 6),
        GenDataEntryPtr(ITEMEDIT, 7),
    };
    int dataIndex = 0;
    uint32_t address = 0;
    CSVItemType *csvType = CSV_Get_ItemType(type->value);
    CSVItemCategory *csvCategory = CSV_Get_ItemCategory(type->value, category->value);
    CSVItemName *csvName = CSV_Get_ItemName(type->value, category->value, ID->value);
    
	if (menu.storage)
        address = ADDR_STORAGE + ((menu.itemSlot - 1) * ITEM_SIZE);
    else
        address = ADDR_INVENTORY + ((menu.itemSlot - 1) * ITEM_SIZE);
    
    Nova_ReadItem(&menu.item, address);
    
    GUID->address = menu.item.base.GUID;
    type->address = menu.item.base.type;
    category->address = menu.item.base.category;
    ID->address = menu.item.base.ID;
    
	if (csvType)
    {
		type->suffix = malloc(MENU_STRING_SIZE);
        sprintf(type->suffix, " (%s)", csvType->name);
        category->max = csvType->max;
    }
    else
    {
        type->suffix = NULL;
        category->max = 0;
    }
    
	if (csvCategory)
    {
        category->suffix = malloc(MENU_STRING_SIZE);
        sprintf(category->suffix, " (%s)", csvCategory->name);
    }
    else
		category->suffix = NULL;
	
    if (csvName)
    {
        slot->suffix = malloc(MENU_STRING_SIZE);
        sprintf(slot->suffix, " (%s)", csvName->name);
    }
    else
        slot->suffix = NULL;
    
    switch (type->value)
    {
    case ITEM_TYPE_WEAPON:
    case ITEM_TYPE_SHIELD:
        data[dataIndex]->name = "Flags";
        data[dataIndex]->dataType = MEMORY_BYTE,
        data[dataIndex]->address = menu.item.data.weapon.flags;
        data[dataIndex]->min = 0;
        data[dataIndex]->max = ITEM_FLAG_MAX;
        dataIndex++;
        data[dataIndex]->name = "Affix";
        data[dataIndex]->dataType = MEMORY_SHORT,
        data[dataIndex]->address = menu.item.data.weapon.affix;
        data[dataIndex]->min = 0;
        data[dataIndex]->max = SHRT_MAX;
        dataIndex++;
        break;
    case ITEM_TYPE_GENERAL:
    case ITEM_TYPE_GRAN:
        data[dataIndex]->name = "Flags";
        data[dataIndex]->dataType = MEMORY_BYTE,
        data[dataIndex]->address = menu.item.data.general.flags;
        data[dataIndex]->min = 0;
        data[dataIndex]->max = ITEM_FLAG_MAX;
        dataIndex++;
        data[dataIndex]->name = "Quantity";
        data[dataIndex]->dataType = MEMORY_SHORT,
        data[dataIndex]->address = menu.item.data.general.quantity;
        data[dataIndex]->min = 0;
        data[dataIndex]->max = SHRT_MAX;
        dataIndex++;
        break;
    }
    
    for (int i = dataIndex; i < MENU_MAX_OPTIONS; i++)
        data[i]->name = NULL;
    
    menu.size = MENU_ITEMEDIT_DATA + dataIndex;
	
	if (dataIndex == 0)
		menu.size--;
}

void Menu_ItemEdit_Slot_Change()
{
    menu.itemSlot = menuEntries[menu.page][menu.index[menu.page]].value;
}

MenuEntry *Menu_GetEntry()
{
    return &menuEntries[menu.page][menu.index[menu.page]];
}
