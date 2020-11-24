#include "guis/gui_main.hpp"
#include "type.hpp"

GuiMain::GuiMain() : Gui()
{
    button_one = new Button(300, 300, 200, 67,"first button");
    tmp = 1;
    //add函数 绑定button
    auto f = std::bind(&GuiMain::add, this);
    button_one->SetInputAction(f);
}

GuiMain::~GuiMain()
{
}
void GuiMain::add()
{
    tmp++;
}
void GuiMain::Draw()
{
    Gui::BeginDraw();
    ////////////////
    Gui::ClearScreen();

    char t1[20];
    sprintf(t1,"%d",tmp);
    this->DrawString(500,500,t1);
    if(MousebPressed())
        button_one->OnMouseInput(mouse_input);
    button_one->Draw(this);


    ////////////////
    Gui::EndDraw();
}
void GuiMain::OnKeyBoardInput(KeyBoard state)
{   
    keystate = state;
}
void GuiMain::OnMouseInput(sMouseState* m_mouse)
{
    mouse_input = m_mouse;
}