#ifndef MEMORY_H
#define MEMORY_H

#include "Common.h"

enum
{
    MEMORY_BYTE,
    MEMORY_SHORT,
    MEMORY_INT,
};

int8_t Memory_ReadByte(uint32_t);
int16_t Memory_ReadShort(uint32_t);
int32_t Memory_ReadInt(uint32_t);

void Memory_WriteByte(uint32_t, int8_t);
void Memory_WriteShort(uint32_t, int16_t);
void Memory_WriteInt(uint32_t, int32_t);

#endif // MEMORY_H
