#pragma once 

#include<switch.h>
#include "guis/gui.hpp"
class Widget
{
public:

    Widget();
    virtual ~Widget();

    static void HandleKeyBoardInput(KeyBoard keystate,Widget* widget);
    static void HandleMouseInput(sMouseState* m_mouse,Widget* widget);


    virtual void Draw(Gui* gui)=0;
    virtual void OnKeyBoardInput(KeyBoard keystate)=0;
    virtual void OnMouseInput(sMouseState* mouse)=0;

    sMouseState* m_mouse;
    KeyBoard keystate;

protected:
    Gui* gui;
    bool IsClip(uint32_t x, uint32_t y);
    uint32_t x,y,w,h;
private:

};