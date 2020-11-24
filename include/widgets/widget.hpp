#pragma once 

#include<switch.h>
#include "guis/gui.hpp"
class Widget
{
public:

    Widget();
    virtual ~Widget();


    virtual void Draw(Gui* gui)=0;
    virtual void OnKeyBoardInput(KeyBoard keystate)=0;
    virtual void OnMouseInput(sMouseState* mouse)=0;
protected:
    Gui* gui;
    sMouseState* m_mouse;

private:
};