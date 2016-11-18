#include "CSV.h"

CSVItemType *ItemTypes;
CSVItemCategory *ItemCategories;
CSVItemName *ItemNames;

char *CSV_GetData(const char *fileName)
{
    int f = sceIoOpen(fileName, SCE_O_RDONLY, 0777);
    SceIoStat stat;
    char *data;
    
    sceIoGetstat(fileName, &stat);
    data = malloc(stat.st_size);
    sceIoRead(f, data, stat.st_size);
    sceIoClose(f);
    
    return data;
}

void CSV_Parse_ItemTypes()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMTYPES);
    size_t size = 0;
    int segment = 0;
    
    for (char *token; (token = strsep(&data, delimiters)) != NULL;)
    {
        ItemTypes = realloc(ItemTypes, sizeof(CSVItemType) * (size + 1));
        CSVItemType *type = &ItemTypes[size];
        
        if (segment == 0)
        {
            type->name = malloc(CSV_STRING_SIZE);
            strcpy(type->name, token);
            
            segment++;
        }
        else if (segment == 1)
        {
            type->max = strtoul(token, NULL, 0);
            
            segment = 0;
            size++;
        }
    }
    
    Log("Done parsing Item Types\n");
}

void CSV_Parse_ItemCategories()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMCATEGORIES);
    size_t size = 0;
    int segment = 0;
    
    for (char *token; (token = strsep(&data, delimiters)) != NULL;)
    {
        ItemCategories = realloc(ItemCategories, sizeof(CSVItemCategory) * (size + 1));
        CSVItemCategory *category = &ItemCategories[size];
        
        if (segment == 0)
        {
            category->type = strtoul(token, NULL, 0);
            
            segment++;
        }
        else if (segment == 1)
        {
            category->category = strtoul(token, NULL, 0);
            
            segment++;
        }
        else if (segment == 2)
        {
            category->name = malloc(CSV_STRING_SIZE);
            strcpy(category->name, token);
            
            segment = 0;
            size++;
        }
    }
    
    Log("Done parsing Item Categories\n");
}

void CSV_Parse_ItemNames()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMNAMES);
    size_t size = 0;
    int segment = 0;
    
    for (char *token; (token = strsep(&data, delimiters)) != NULL;)
    {
        ItemNames = realloc(ItemNames, sizeof(CSVItemName) * (size + 1));
        CSVItemName *name = &ItemNames[size];
        
        if (segment == 0)
        {
            name->type = strtoul(token, NULL, 0);
            
            segment++;
        }
        else if (segment == 1)
        {
            name->category = strtoul(token, NULL, 0);
            
            segment++;
        }
        else if (segment == 2)
        {
            name->ID = strtoul(token, NULL, 0);
            
            segment++;
        }
        else if (segment == 3)
        {
            name->name = malloc(CSV_STRING_SIZE);
            strcpy(name->name, token);
            
            segment = 0;
            size++;
        }
    }
    
    Log("Done parsing Item Names\n");
}

CSVItemType *CSV_Get_ItemType(uint32_t type)
{
    return &ItemTypes[type];
}

CSVItemCategory *CSV_Get_ItemCategory(uint32_t type, uint32_t category)
{
    size_t size = 0;
    
    while ((&ItemCategories[size])->name != NULL)
        size++;
    
    for (int i = 0; i < size; i++)
        if ((&ItemCategories[i])->type == type && (&ItemCategories[i])->category == category)
            return &ItemCategories[i];
    
    return NULL;
}

CSVItemName *CSV_Get_ItemName(uint32_t type, uint32_t category, uint32_t ID)
{
    size_t size = 0;
    
    while ((&ItemNames[size])->name != NULL)
        size++;
    
    for (int i = 0; i < size - 1; i++)
        if ((&ItemNames[i])->type == type && (&ItemNames[i])->category == category && (&ItemNames[i])->ID == ID)
            return &ItemNames[i];
    
    return NULL;
}
