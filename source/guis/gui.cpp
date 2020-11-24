#include "guis/gui.hpp"
#include "type.hpp"
static uint32_t stride;

Gui::Gui()
{
    fontInit();
}
Gui::~Gui()
{
    fontExit();
}

void Gui::DrawPixel(int32_t x, int32_t y,uint32_t rgba)
{
    if (x >= 1280 || y >= 720 || x < 0 || y < 0)
      return;
    framebuffer[y * g_framebuffer_width + x] = rgba;

}
void Gui::BeginDraw()
{
    this->framebuffer = (uint32_t*)framebufferBegin(&Gui::g_fb_obj,&stride);
}

void Gui::EndDraw()
{
    framebufferEnd(&Gui::g_fb_obj);
}

void Gui::FillRect(int32_t x, int32_t y,int32_t w,int32_t h,uint32_t rgba)
{
    for (int32_t _x = x; _x < x + w; _x++)
        for (int32_t _y = y; _y < y + h; _y++)
            DrawPixel(_x, _y, rgba);
}
bool Gui::fontInit()
{
    rc = plGetSharedFontByType(&font, PlSharedFontType_Standard);
    if (R_FAILED(rc))
        fatalThrow(rc);
    ret = FT_Init_FreeType(&library);
    ret = FT_New_Memory_Face(library,
                                (const FT_Byte *)font.address, /* first byte in memory */
                                font.size,						/* size in bytes        */
                                0,								/* face_index           */
                                &face);
    return true;
}

void Gui::ClearScreen()
{
    memset(framebuffer,0x0,g_framebuffer_height * g_framebuffer_width * sizeof(uint32_t));
}

void Gui::fontExit()
{
    FT_Done_Face(face);
    FT_Done_FreeType(library);
}
void Gui::Draw_text(uint32_t x ,uint32_t y ,const char *str)
{
    ret = FT_Set_Char_Size(
    face,	 /* handle to face object           */
    0,		 /* char_width in 1/64th of points  */
    24 * 64 * 1, /* char_height in 1/64th of points */
    0,		 /* horizontal device resolution    */
    0x60 );	 /* vertical device resolution      */
    uint32_t tmpx = x;
    FT_Error ret = 0;
    FT_UInt glyph_index;
    FT_GlyphSlot slot = face->glyph;

    uint32_t i;
    uint32_t str_size = strlen(str);
    uint32_t tmpchar;
    ssize_t unitcount = 0;

    for (i = 0; i < str_size;)
    {
        unitcount = decode_utf8(&tmpchar, (const uint8_t *)&str[i]);
        if (unitcount <= 0)
            break;
        i += unitcount;

        if (tmpchar == '\n')
        {
            tmpx = x;
            y += face->size->metrics.height / 64;
            continue;
        }

        glyph_index = FT_Get_Char_Index(face, tmpchar);
        //If using multiple fonts, you could check for glyph_index==0 here and attempt using the FT_Face for the other fonts with FT_Get_Char_Index.

        ret = FT_Load_Glyph(
            face,		 /* handle to face object */
            glyph_index, /* glyph index           */
            FT_LOAD_DEFAULT);

        if (ret == 0)
        {
            ret = FT_Render_Glyph(face->glyph,			  /* glyph slot  */
                                    FT_RENDER_MODE_NORMAL); /* render mode */
        }

        if (ret)
            return;

        Draw_glyph(&slot->bitmap, tmpx + slot->bitmap_left, y - slot->bitmap_top);

        tmpx += slot->advance.x >> 6;
        y += slot->advance.y >> 6;
    }
}
void Gui::Draw_glyph(FT_Bitmap *bitmap, uint32_t x, uint32_t y)
{
    uint32_t framex, framey;
    uint32_t tmpx, tmpy;
    u8 *imageptr = bitmap->buffer;
    if (bitmap->pixel_mode != FT_PIXEL_MODE_GRAY)
        return;

    for (tmpy = 0; tmpy < bitmap->rows; tmpy++)
    {
        for (tmpx = 0; tmpx < bitmap->width; tmpx++)
        {
            framex = x + tmpx;
            framey = y + tmpy;
            if(imageptr[tmpx]==0xff)
                if (framex >= (uint32_t)0 && framex < (uint32_t)g_framebuffer_width && framey >= (uint32_t)0 && framey < (uint32_t)g_framebuffer_height)					
                    framebuffer[framey * g_framebuffer_width + framex] = FG_BLUE;
        }
        imageptr += bitmap->pitch;
    }
}

void Gui::DrawString(uint32_t x ,uint32_t y ,const char *str)
{
    Draw_text(x ,y ,str);
}

void Gui::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, const int32_t rgba)
{
    DrawLine(x,y,x+w,y,rgba);
    DrawLine(x+w,y,x+w,y+h,rgba);
    DrawLine(x+w,y+h,x,y+h,rgba);
    DrawLine(x,y+h,x,y,rgba);
}

void Gui::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const uint32_t rgba = FG_RED)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = abs(dx);
    dy1 = abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        DrawPixel(x, y, rgba);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    y = y + 1;
                else
                    y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            DrawPixel(x, y, rgba);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        DrawPixel(x, y, rgba);
        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                    x = x + 1;
                else
                    x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            DrawPixel(x, y, rgba);
        }
    }
}
void Gui::DrawShadow(int32_t x, int32_t y,int32_t w,int32_t h)
{
    FillRect(x+1,y+1,w-2,h-2,FG_GREY);
}
