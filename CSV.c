#include "CSV.h"

CSVItemType *ItemTypes;
CSVItemCategory *ItemCategories;
CSVItemName *ItemNames;

size_t ItemCategoriesSize = 0;
size_t ItemNamesSize = 0;

char *CSV_GetData(const char *fileName)
{
    FILE *f = fopen(fileName, "rb");
    char *data;
    int size;
    
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    data = (char *)malloc(size);
    fread(data, size, 1, f);
    fclose(f);
    
    return data;
}

void CSV_Parse_ItemTypes()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMTYPES);
    size_t size = 0;
    int segment = 0;
    
    for (char *token; (token = strsep(&data, delimiters));)
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
    
    for (char *token; (token = strsep(&data, delimiters));)
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
    
	ItemCategoriesSize = size;
	
    Log("Done parsing Item Categories\n");
}

void CSV_Parse_ItemNames()
{
    const char *delimiters = ",\n";
    char *data = CSV_GetData(CSV_FILE_ITEMNAMES);
    size_t size = 0;
    int segment = 0;
    
    for (char *token; (token = strsep(&data, delimiters));)
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
    
	ItemNamesSize = size;
	
    Log("Done parsing Item Names\n");
}

CSVItemType *CSV_Get_ItemType(uint32_t type)
{
    return &ItemTypes[type];
}

CSVItemCategory *CSV_Get_ItemCategory(uint32_t type, uint32_t category)
{
	for (int i = 0; i < ItemCategoriesSize; i++)
        if ((&ItemCategories[i])->type == type && (&ItemCategories[i])->category == category)
            return &ItemCategories[i];
    
	return NULL;
}

CSVItemName *CSV_Get_ItemName(uint32_t type, uint32_t category, uint32_t ID)
{
	for (int i = 0; i < ItemNamesSize; i++)
        if ((&ItemNames[i])->type == type && (&ItemNames[i])->category == category && (&ItemNames[i])->ID == ID)
            return &ItemNames[i];
    
    return NULL;
}
