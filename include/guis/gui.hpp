#pragma once

#include <switch.h>

extern "C"
{
#include <ft2build.h>
#include FT_FREETYPE_H
}

#include "type.hpp"

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
    uint32_t* framebuffer;
    static inline Framebuffer g_fb_obj;
    static inline int32_t g_framebuffer_width = 1280;
    static inline int32_t g_framebuffer_height = 720;

    Gui();
    virtual ~Gui();

    virtual void Draw()=0;
    virtual void OnKeyBoardInput(KeyBoard keystate)=0;
    virtual void OnMouseInput(sMouseState* mouse)=0;

    void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const uint32_t rgba );
	void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, const int32_t rgba);
    void FillRect(int32_t x, int32_t y,int32_t w,int32_t h,uint32_t rgba);
    void DrawString(uint32_t x ,uint32_t y ,const char *str);
    void DrawShadow(int32_t x, int32_t y,int32_t w,int32_t h);




protected:  
    virtual void BeginDraw();
    virtual void EndDraw();
    void ClearScreen();

    bool MousebPressed() {return mouse_input[0].bPressed;}
	bool MousebHeld() {return mouse_input[0].bHeld;}
	bool MousebReleased() {return mouse_input[0].bReleased;}

	bool KeyDown(HidControllerKeys key) {return (keystate.kDown & key);}
	bool KeyHeld(HidControllerKeys key) {return (keystate.kHeld & key);}
	bool KeyUp(HidControllerKeys key) {return (keystate.kUp & key);}
    
    sMouseState* mouse_input;
    KeyBoard keystate;
private:
    //font
	Result rc ;
	FT_Error ret = 0;
	PlFontData font;
	FT_Library library;
	FT_Face face;
    uint32_t fontsize;
    uint32_t fontcolor;

    void Draw_text(uint32_t x ,uint32_t y ,const char *str);
	void Draw_glyph(FT_Bitmap *bitmap, uint32_t x, uint32_t y);
    inline void DrawPixel(int32_t x, int32_t y,uint32_t rgba);

    bool fontInit();
    void fontExit();




};