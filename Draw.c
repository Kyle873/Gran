#include "Draw.h"

DrawData drawData;

int Draw_Init()
{
    SceDisplayFrameBuf framebuf;
    framebuf.size = sizeof(SceDisplayFrameBuf);
    sceDisplayGetFrameBuf(&framebuf, SCE_DISPLAY_SETBUF_IMMEDIATE);
    
    drawData.frameBuffer = framebuf;
    
    if (drawData.frameBuffer.pitch == 0 || drawData.frameBuffer.pixelformat != 0)
        return -1;
    
    return 0;
}

void Draw_Clear(uint32_t color)
{
    Draw_SetPosition(0, 0);
    
    uint32_t prevColor = Draw_SetFGColor(color);
    
    Draw_RectangleFill(SCREEN_WIDTH, SCREEN_HEIGHT);
    Draw_SetFGColor(prevColor);
}

uint32_t Draw_SetFGColor(uint32_t color)
{
    uint32_t prevColor = drawData.FGColor;
    
    drawData.FGColor = color;
    
    return prevColor;
}

uint32_t Draw_SetBGColor(uint32_t color)
{
    uint32_t prevColor = drawData.BGColor;
    
    drawData.BGColor = color;
    
    return prevColor;
}

void Draw_SetPosition(uint32_t x, uint32_t y)
{
    drawData.pos.x = x;
    drawData.pos.y = y;
}

int Draw_Print(const char *text)
{
    int c, i, j, l;
    uint8_t *font;
    uint32_t *VRAMPtr;
    uint32_t *VRAM;
    
    for (c = 0; text[c] != '\0'; c++)
    {
        if (text[c] == '\r')
            continue;
        
        VRAM = ((uint32_t *)drawData.frameBuffer.base) + drawData.pos.x + drawData.pos.y * SCREEN_FB_WIDTH;
        font = &debugFont[(int)text[c] * 8];
        
        for (i = l = 0; i < SCREEN_GLYPH_W; i++, l += SCREEN_GLYPH_W, font++)
        {
            VRAMPtr = VRAM;
            
            for (j = 0; j < SCREEN_GLYPH_W; j++)
            {
                if ((*font & (128 >> j)))
                    *VRAMPtr = drawData.FGColor;
                else
                    *VRAMPtr = drawData.BGColor;
                
                VRAMPtr++;
            }
            
            VRAM += SCREEN_FB_WIDTH;
        }
        
        drawData.pos.x += SCREEN_GLYPH_W;
    }
    
    return c;
}

int Draw_Printf(const char *format, ...)
{
    char buffer[1024];
    
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    Draw_Print(buffer);
    
    return ret;
}

void Draw_Line(uint32_t xDest, uint32_t yDest)
{
    uint32_t x = xDest - drawData.pos.x;
    uint32_t y = yDest - drawData.pos.y;
    uint32_t length = (uint32_t)sqrt((uint32_t)(x * x) + (uint32_t)(y * y));
    uint32_t xAdd = x / length;
    uint32_t yAdd = y / length;
    
    x = drawData.pos.x;
    y = drawData.pos.y;
    
    for (int i = 0; i < length; i++)
    {
        Draw_Pixel(x, y);
        
        x += xAdd;
        y += yAdd;
    }
}

void Draw_LineXY(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    uint32_t x = x2 - x1;
    uint32_t y = y2 - y1;
    uint32_t length = (uint32_t)sqrt((uint32_t)(x * x) + (uint32_t)(y * y));
    uint32_t xAdd = x / length;
    uint32_t yAdd = y / length;
    
    x = x1;
    y = y1;
    
    for (int i = 0; i < length; i++)
    {
        Draw_Pixel(x, y);
        
        x += xAdd;
        y += yAdd;
    }
}

void Draw_Rectangle(uint32_t width, uint32_t height)
{
    Position pos = drawData.pos;
    
    Draw_LineXY(pos.x, pos.y, pos.x + width, pos.y);
    Draw_LineXY(pos.x, pos.y, pos.x, pos.y + height);
    Draw_LineXY(pos.x + width, pos.y, pos.x + width, pos.y + height);
    Draw_LineXY(pos.x, pos.y + height, pos.x + width, pos.y + height);
}

void Draw_RectangleFill(uint32_t width, uint32_t height)
{
    Position pos = drawData.pos;
    uint32_t *VRAM = &(((uint32_t *)drawData.frameBuffer.base)[(pos.y * SCREEN_WIDTH) + pos.x]);
    
    while (height--)
    {
        for (uint32_t x = 0; x < width; x++)
            VRAM[x] = drawData.FGColor;
        
        VRAM += SCREEN_WIDTH;
    }
}

void Draw_Circle(uint32_t radius)
{
    Position pos = drawData.pos;
    
    pos.x += radius / 2;
    pos.y += radius / 2;
    
    for (int i = radius; i >= 0; i--)
        for (float j = 0; j < 360.0f; j++)
        {
            uint32_t x = pos.x + radius * cos(j * M_PI / 180.0f);
            uint32_t y = pos.y + radius * sin(j * M_PI / 180.0f);
            
            Draw_Pixel(x, y);
        }
}

void Draw_CircleFill(uint32_t radius)
{
    Position pos = drawData.pos;
    
    pos.x += radius / 2;
    pos.y += radius / 2;
    
    for (int i = radius; i >= 0; i--)
        for (float j = 0; j < 360.0f; j++)
        {
            uint32_t x = pos.x + (radius - i) * cos(j * M_PI / 180.0f);
            uint32_t y = pos.y + (radius - i) * sin(j * M_PI / 180.0f);
            
            Draw_Pixel(x, y);
        }
}
