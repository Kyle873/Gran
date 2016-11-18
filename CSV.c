#include "CSV.h"

CSVItemName *ItemNames;
char *ItemTypes[MAX_ITEM_TYPES];
CSVItemCategory *ItemCategories;

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

void CSV_Parse_ItemNames()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMNAMES);
    size_t num = 0;
    int segment = 0;
        
    for (char *token; (token = strsep(&data, delimiters)) != NULL;)
    {
        ItemNames = realloc(ItemNames, sizeof(CSVItemName) * (num + 1));
        CSVItemName *name = &ItemNames[num];
        
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
            num++;
        }
    }
    
    flog("Done parsing Item Names\n");
}

void CSV_Parse_ItemTypes()
{
    char *data = CSV_GetData(CSV_FILE_ITEMTYPES);
    int index = 0;
    
    for (char *token = strtok(data, "\n"); token != NULL; token = strtok(NULL, "\n"))
        ItemTypes[index++] = token;
    
    flog("Done parsing Item Types\n");
}

void CSV_Parse_ItemCategories()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMCATEGORIES);
    size_t num = 0;
    int segment = 0;
        
    for (char *token; (token = strsep(&data, delimiters)) != NULL;)
    {
        ItemCategories = realloc(ItemCategories, sizeof(CSVItemCategory) * (num + 1));
        CSVItemCategory *category = &ItemCategories[num];
        
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
            num++;
        }
    }
    
    flog("Done parsing Item Categories\n");
}
