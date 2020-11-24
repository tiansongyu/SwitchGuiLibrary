#include "guis/gui_about.hpp"
#include "type.hpp"

GuiAbout::GuiAbout() : Gui()
{
    std::vector<std::string> vec_str;
    vec_str.push_back(std::string("hello"));
    vec_str.push_back(std::string("world"));
    vec_str.push_back(std::string("tiansongyu"));

    list = new List(100,100,vec_str);
}

GuiAbout::~GuiAbout()
{
}

void GuiAbout::Draw()
{
    Gui::BeginDraw();
    Gui::ClearScreen();

    list->Draw(this);

    Gui::EndDraw();
    return;
}
void GuiAbout::OnKeyBoardInput(KeyBoard state)
{

}
void GuiAbout::OnMouseInput(sMouseState* m_mouse)
{

}