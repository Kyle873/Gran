#ifndef DRAW_H
#define DRAW_H

#include "Common.h"

#define SCREEN_WIDTH        (960)
#define SCREEN_HEIGHT       (544)
#define SCREEN_FB_WIDTH     (960)
#define SCREEN_FB_SIZE      (2 * 1024 * 1024)
#define SCREEN_FB_ALIGN     (256 * 1024)
#define SCREEN_GLYPH_W      (8)
#define SCREEN_GLYPH_H      (8)

#define COLOR_DEFAULT_FG    COLOR_WHITE
#define COLOR_DEFAULT_BG    COLOR_NONE

// Because C11 doesn't include this
#define M_PI                (3.14159265358979323846)

enum
{
    COLOR_NONE =    0x00000000,
    COLOR_BLACK =   0xFF000000,
    COLOR_GREY =    0xFF7F7F7F,
    COLOR_RED =     0xFF0000FF,
    COLOR_ORANGE =  0xFF007FFF,
    COLOR_YELLOW =  0xFF00FFFF,
    COLOR_GREEN =   0xFF00FF00,
    COLOR_BLUE =    0xFFFFFF00,
    COLOR_CYAN =    0xFFFFFF00,
    COLOR_MAGENTA = 0xFFFF00FF,
    COLOR_WHITE =   0xFFFFFFFF,
};

typedef struct
{
    uint32_t x;
    uint32_t y;
} Position;

typedef struct
{
    SceDisplayFrameBuf frameBuffer;
    
    Position pos;
    
    uint32_t FGColor;
    uint32_t BGColor;
} DrawData;

extern uint8_t debugFont[];

extern DrawData drawData;

inline static void Draw_Pixel(uint32_t x, uint32_t y)
{
    ((uint32_t *)drawData.frameBuffer.base)[x + y * SCREEN_FB_WIDTH] = drawData.FGColor;
}

int Draw_Init();

void Draw_Clear(uint32_t);

uint32_t Draw_SetFGColor(uint32_t);
uint32_t Draw_SetBGColor(uint32_t);
void Draw_SetPosition(uint32_t, uint32_t);

int Draw_Print(const char *);
int Draw_Printf(const char *, ...);
void Draw_Line(uint32_t, uint32_t);
void Draw_LineXY(uint32_t, uint32_t, uint32_t, uint32_t);
void Draw_Rectangle(uint32_t, uint32_t);
void Draw_RectangleFill(uint32_t, uint32_t);
void Draw_Circle(uint32_t);
void Draw_CircleFill(uint32_t);

#endif // DRAW_H
