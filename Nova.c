#include "Nova.h"

void Nova_ReadItem(Item *item, uint32_t address)
{
    *item = (Item)
    {
        .base =
        {
            .GUID = address,
            .type = address + 4,
            .category = address + 6,
            .ID = address + 10,
        },
        
        .data =
        {
            .weapon =
            {
                .flags = address + 12,
                .affix = address + 13,
            },
            
            .costume =
            {
                .flags = address + 12,
                .unused = address + 13,
                .colors =
                {
                    {
                        .hue = address + 14,
                        .saturation = address + 16,
                        .value = address + 18,
                    },
                    {
                        .hue = address + 20,
                        .saturation = address + 22,
                        .value = address + 24,
                    },
                },
            },
            
            .general =
            {
                .flags = address + 12,
                .unused = address + 13,
                .quantity = address + 14,
            },
            
            .attachment =
            {
                .affix = address + 12,
                .unknown = address + 14,
                .flags = address + 15,
                .itemPtr = address + 16,
                .x = address + 20,
                .z = address + 24,
                .y = address + 28,
                .rotationX = address + 32,
                .rotationY = address + 36,
                .scale = address + 40,
            },
            
            .shield =
            {
                .flags = address + 12,
                .affix = address + 13,
            },
            
            .core =
            {
                .affix = address + 12,
            }
        },
    };
}
