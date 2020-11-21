#pragma once

#include <switch.h>

extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
}


struct RGBA
{
	union 
	{
		uint32_t rgba;
		uint8_t color[4];
	};
};

class Gui 
{
public:
    u32* framebuffer;
    static inline Framebuffer g_fb_obj;
    static inline int32_t g_framebuffer_width = 1280;
    static inline int32_t g_framebuffer_height = 720;

    Gui();
    virtual ~Gui();

    virtual void Draw()=0;

    void DrawRect(int32_t x, int32_t y,int32_t w,int32_t h,uint32_t rgba);
    void DrawPixel(int32_t x, int32_t y,uint32_t rgba);

protected:  
    virtual void BeginDraw();
    virtual void EndDraw();

private:
    //font
	Result rc ;
	FT_Error ret = 0;
	PlFontData font;
	FT_Library library;
	FT_Face face;
};