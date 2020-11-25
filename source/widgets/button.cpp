#include "widgets/button.hpp"

Button::Button(uint32_t _x, uint32_t _y, uint32_t _w, uint32_t _h, std::string _stext) 
{
    x = _x ;
    y = _y ;
    w = _w ;
    h = _h ;
    stext = _stext;
}
Button::~Button()
{
}
void Button::Draw(Gui *_gui)
{    
    gui = _gui;
    _gui->DrawRect(this->x, this->y, this->w, this->h, FG_RED);
    _gui->DrawShadow(this->x,this->y,this->w,this->h);
    
    if(IsClip(m_mouse[0].mouse_pos_x,m_mouse[0].mouse_pos_y) && m_mouse[0].bHeld)
        _gui->FillRect(x+6,y+6,w-12,h-12,FG_DARK_GREY);

    _gui->DrawString(this->x, this->y + this->h, this->GetText().c_str());

    memset(m_mouse,0x0,sizeof(sMouseState));
}

void Button::OnKeyBoardInput(KeyBoard keystate)
{
    
}

void Button::OnMouseInput(sMouseState *mouse)
{
    if(IsClip(mouse[0].mouse_pos_x,mouse[0].mouse_pos_y) && m_mouse[0].bPressed)
        action(gui);
}

void Button::SetInputAction(std::function<void(Gui *gui)> _action)
{
    action = _action;
}

std::string Button::GetText()
{
    return stext;
}

