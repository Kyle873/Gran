#include "Nova.h"

void Nova_CalculateOffset()
{
    // Delay so that the game has time to populate the blocks with it's initial data
    sceKernelDelayThread(3 * 1000 * 1000);
    
    Log("Nova_CalculateOffset: Beginning Nova base block scan...\n");
    
    for (uint32_t block = ADDR_BLOCK_BASE + ADDR_BLOCK_HEADER_SIZE, num = 0; block < ADDR_BLOCK_BASE + ADDR_BLOCK_HEADER_SIZE + (ADDR_BLOCK_NOVA_OFFSET * ADDR_BLOCK_MAX); block += ADDR_BLOCK_NOVA_OFFSET, num++)
    {
        size_t count = 0;
        
        Logf("Nova_CalculateOffset: Starting on block %X (%d/%d)\n", block, num + 1, ADDR_BLOCK_MAX);
        
        for (uint32_t offset = block; offset < block + (ADDR_BLOCK_THRESHOLD * 4); offset += 4)
        {
            Logf("Nova_CalculateOffset: Checking at offset %X\n", offset);
            
            if (Memory_ReadInt(offset) == ADDR_BLOCK_BLANK_AOB)
            {
                count++;
                
                Logf("Nova_CalculateOffset: Empty memory found (0x%X), threshold count is %d/%d\n", ADDR_BLOCK_BLANK_AOB, count, ADDR_BLOCK_THRESHOLD);
            }
            
            if (count >= ADDR_BLOCK_THRESHOLD)
            {
                MemoryOffset = num + 1;
                
                Logf("Nova_CalculateOffset: Threshold reached, base memory offset is %d (%X)\n", MemoryOffset, block);
                return;
            }
        }
        
        Log("Nova_CalculateOffset: Nothing found here, moving on...\n");
    }
    
    Log("Nova_CalculateOffset: Nothing found, Assuming default memory offset\n");
    
    MemoryOffset = 0;
}

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
