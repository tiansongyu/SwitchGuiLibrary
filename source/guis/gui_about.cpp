#include "guis/gui_about.hpp"
#include "type.hpp"

GuiAbout::GuiAbout():Gui()
{

}

GuiAbout::~GuiAbout()
{

}

void GuiAbout::Draw()
{
    Gui::BeginDraw();
    Gui::DrawRect(10,10,200,200,FG_RED);
    Gui::EndDraw();
    return ;
}