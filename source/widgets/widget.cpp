#include "widgets/widget.hpp"


Widget::Widget()
{
    m_mouse = new sMouseState[5];
    
    
}
Widget::~Widget()
{

}



void Widget::HandleKeyBoardInput(KeyBoard _keystate,Widget* widget)
{
    widget->keystate = _keystate;
}

void Widget::HandleMouseInput(sMouseState* _m_mouse,Widget* widget)
{
    widget->m_mouse = _m_mouse;
}

bool Widget::IsClip(uint32_t pos_x, uint32_t pos_y)
{
    if (pos_x < x || pos_x > x + w || pos_y < y || pos_y > y + h)
        return false;
    else
        return true;
}
