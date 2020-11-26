#include "widgets/list.hpp"

List::List(uint32_t _x, uint32_t _y, std::vector<std::string> &_stext)
{
    x = _x;
    y = _y;
    stext = _stext;

    number = stext.size();
    curr_index = 1;

    w = x_wight;
    h = number * y_offset;
}
List::~List()
{
}

void List::Draw(Gui *_gui)
{
    gui = _gui;

    _gui->DrawRect(x, y, w, h, FG_DARK_RED);
    for (uint32_t i = 0; i < number; i++)
    {
        if (curr_index == i + 1)
            _gui->FillRect(x, y + i * y_offset, 200, 100, FG_YELLOW);
        _gui->DrawStringAligned(x, y + i * y_offset , this->GetWigth(), this->GetHeight() , stext[i].c_str());
    }
}

void List::SetInputAction(std::vector<std::function<void(Gui *gui)>> _vec_function)
{
    vec_function = _vec_function;
}

void List::OnKeyBoardInput(KeyBoard keystate)
{

    if (keystate.kDown & KEY_DOWN)
    {
        if (++curr_index > number)
            curr_index = 1;
    }
    if (keystate.kDown & KEY_UP)
    {
        if (--curr_index < 1)
            curr_index = number;
    }

    if (keystate.kDown & KEY_X)
    {
        (vec_function[(int)curr_index - 1])(this->gui);
    }
}

void List::OnMouseInput(sMouseState *mouse)
{
    if (Widget::IsClip(mouse[0].mouse_pos_x, mouse[0].mouse_pos_y))
    {
        curr_index = (mouse[0].mouse_pos_y - y) / y_offset + 1;
    }
}