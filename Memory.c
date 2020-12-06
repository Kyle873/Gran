#include "Memory.h"

int8_t Memory_ReadByte(uint32_t address)
{
    return (int8_t)(*(int8_t *)address);
}

int16_t Memory_ReadShort(uint32_t address)
{  
    return (int16_t)(*(int16_t *)address);
}

int32_t Memory_ReadInt(uint32_t address)
{
    return (*(int32_t *)address);
}

void Memory_WriteByte(uint32_t address, int8_t value)
{
    *(uint32_t *)address = value;
}

void Memory_WriteShort(uint32_t address, int16_t value)
{
    *(uint32_t *)address = value;
}

void Memory_WriteInt(uint32_t address, int32_t value)
{
    *(uint32_t *)address = value;
}
