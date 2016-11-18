#ifndef ADDRESS_H
#define ADDRESS_H

// Block
#define ADDR_BLOCK_BASE         (0x870FFED0)
#define ADDR_BLOCK_HEADER_SIZE  (0x10)
#define ADDR_BLOCK_SIZE         (0x210)
#define ADDR_BLOCK_NOVA_OFFSET  (0x00100000)
#define ADDR_BLOCK_BLANK_AOB    (0xCCCCCCCC)
#define ADDR_BLOCK_MAX          (8)
#define ADDR_BLOCK_THRESHOLD    (32)

// Player
#define ADDR_LEVEL          (0x871B0790)
#define ADDR_EXP            (0x871B07A4)
#define ADDR_GRANENERGY     (0x871644AC)
#define ADDR_MAXHP          (0x871B0794)
#define ADDR_CURRENTHP      (0x871B0798)
#define ADDR_MAXGP          (0x871B079C)
#define ADDR_CURRENTGP      (0x871B07A0)

// Inventory
#define ADDR_INVENTORY      (0x871200B0)
#define ADDR_STORAGE        (0x87122340)

#endif // ADDRESS_H
