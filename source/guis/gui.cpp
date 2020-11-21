#include "guis/gui.hpp"
static u32 stride;

Gui::Gui()
{

}
Gui::~Gui()
{

}

void Gui::DrawPixel(int32_t x, int32_t y,uint32_t rgba)
{
    if (x >= 1280 || y >= 720 || x < 0 || y < 0)
      return;
    framebuffer[y * g_framebuffer_width + x] = rgba;

}
void Gui::BeginDraw()
{
    this->framebuffer = (u32*)framebufferBegin(&Gui::g_fb_obj,&stride);
}

void Gui::EndDraw()
{
    framebufferEnd(&Gui::g_fb_obj);
}

void Gui::DrawRect(int32_t x, int32_t y,int32_t w,int32_t h,uint32_t rgba)
{
    for (int32_t _x = x; _x < x + w; _x++)
        for (int32_t _y = y; _y < y + h; _y++)
            DrawPixel(_x, _y, rgba);
}