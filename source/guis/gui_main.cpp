#include "guis/gui_main.hpp"
#include "type.hpp"

GuiMain::GuiMain():Gui()
{

}

GuiMain::~GuiMain()
{

}

void GuiMain::Draw()
{
    Gui::BeginDraw();
    Gui::DrawRect(10,10,200,200,FG_BLUE);
    Gui::EndDraw();
    return ;
}