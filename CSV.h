#ifndef CSV_H
#define CSV_H

#include "Common.h"

#define CSV_FILE_ITEMNAMES      "ux0:/data/Gran/ItemNames.csv"
#define CSV_FILE_ITEMTYPES      "ux0:/data/Gran/ItemTypes.csv"
#define CSV_FILE_ITEMCATEGORIES "ux0:/data/Gran/ItemCategories.csv"

#define CSV_STRING_SIZE         (256)

#define MAX_ITEM_TYPES          (7)

typedef struct
{
    uint32_t type;
    uint32_t category;
    uint32_t ID;
    char *name;
} CSVItemName;

typedef struct
{
    uint32_t type;
    uint32_t category;
    char *name;
} CSVItemCategory;

typedef struct
{
    uint32_t ID;
    char *name;
} CSVAffixInfo;

extern CSVItemName *ItemNames;
extern char *ItemTypes[];
extern CSVItemCategory *ItemCategories;

char *CSV_GetData(const char *);

void CSV_Parse_ItemNames();
void CSV_Parse_ItemTypes();
void CSV_Parse_ItemCategories();

#endif // CSV_H
