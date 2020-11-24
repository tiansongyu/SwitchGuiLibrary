#include "widgets/list.hpp"

List::List(uint32_t _x, uint32_t _y,  std::vector<std::string> &_stext) : x(_x), y(_y), stext(_stext)
{
    m_mouse = new sMouseState[5];
    number = stext.size();
}
List::~List()
{
}

void List::Draw(Gui *_gui)
{
    uint32_t w = 200;
    uint32_t h = number * 100;

    _gui->DrawRect(x,y,w,h,FG_DARK_RED);
    
    uint32_t y_start_offset = 60;
    uint32_t y_offset = 100;
    for(uint32_t i=1;i<number+1;i++)
    {
        _gui->DrawString(x+ 5,i * y_offset + y_start_offset,stext[i-1].c_str());
    }

}

void List::OnKeyBoardInput(KeyBoard keystate)
{

}

void List::OnMouseInput(sMouseState *mouse)
{

}