#ifndef NOVA_H
#define NOVA_H

#include "Common.h"
#include "Memory.h"

#define ITEM_SIZE           (44)

#define MAX_INV_ENTRIES     (200)
#define MAX_STORAGE_ENTRIES (2000)

enum
{
    ITEM_FLAG_NEW = 0x01,
    ITEM_FLAG_LOCKED = 0x02,
    
    ITEM_FLAG_MAX,
};

enum
{
    ITEM_TYPE_NONE,
    ITEM_TYPE_WEAPON,
    ITEM_TYPE_COSTUME,
    ITEM_TYPE_GENERAL,
    ITEM_TYPE_ATTACHMENT,
    ITEM_TYPE_SHIELD,
    ITEM_TYPE_CORE,
};

// Structures hold addresses to the data, not the data itself!

typedef struct
{
    uint32_t hue;
    uint32_t saturation;
    uint32_t value;
} HSV;

typedef struct
{
    uint32_t GUID;
    uint32_t type;
    uint32_t category;
    uint32_t ID;
} ItemBase;

// TODO: Investigate Weapon data
typedef struct
{
    uint32_t flags;
    uint32_t affix;
} ItemDataWeapon;

typedef struct
{
    uint32_t flags;
    uint32_t unused;
    HSV colors[2];
} ItemDataCostume;

typedef struct
{
    uint32_t flags;
    uint32_t unused;
    uint32_t quantity;
} ItemDataGeneral;

typedef struct
{
    uint32_t affix;
    uint32_t unknown;
    uint32_t flags;
    uint32_t itemPtr;
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t rotationX;
    uint32_t rotationY;
    uint32_t scale;
} ItemDataAttachment;

typedef struct
{
    uint32_t flags;
    uint32_t affix;
} ItemDataShield;

// TODO: Investigate Core data
typedef struct
{
    uint32_t affix;
} ItemDataCore;

typedef struct
{
    ItemDataWeapon weapon;
    ItemDataCostume costume;
    ItemDataGeneral general;
    ItemDataAttachment attachment;
    ItemDataShield shield;
    ItemDataCore core;
} ItemData;

typedef struct
{
    ItemBase base;
    ItemData data;
} Item;

void Nova_ReadItem(Item *, uint32_t);

#endif // NOVA_H
