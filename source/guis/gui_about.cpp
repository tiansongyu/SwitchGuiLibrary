#include "guis/gui_about.hpp"
#include "type.hpp"

GuiAbout::GuiAbout() : Gui()
{
    std::vector<std::string> vec_str;
    vec_str.push_back(std::string("hello"));
    vec_str.push_back(std::string("world"));
    vec_str.push_back(std::string("tiansongyu"));

    list = new List(100, 100, vec_str);

    tmp_one = 1;
    tmp_two = 2;
    tmp_three = 3;

    auto f1 = std::bind(&GuiAbout::Add_first, this);
    auto f2 = std::bind(&GuiAbout::Add_second, this);
    auto f3 = std::bind(&GuiAbout::Add_third, this);

    std::vector<std::function<void(Gui*gui)> > vec;
    vec.push_back(f1);
    vec.push_back(f2);
    vec.push_back(f3);

    list->SetInputAction(vec);

}

GuiAbout::~GuiAbout()
{
}

void GuiAbout::Add_first()
{
    tmp_one++;
}

void GuiAbout::Add_second()
{
    tmp_two++;
}
void GuiAbout::Add_third()
{
    tmp_three++;
}

void GuiAbout::Draw()
{
    Gui::BeginDraw();
    Gui::ClearScreen();

    list->Draw(this);

    char t1[20];
    sprintf(t1, "%d", tmp_one);
    this->DrawString(500, 500, t1);

    char t2[20];
    sprintf(t2, "%d", tmp_two);
    this->DrawString(500, 600, t2);

    char t3[20];
    sprintf(t3, "%d", tmp_three);
    this->DrawString(500, 700, t3);


    Gui::EndDraw();
}
void GuiAbout::OnKeyBoardInput(KeyBoard state)
{
    List::HandleKeyBoardInput(state, list);
    list->OnKeyBoardInput(state);
}
void GuiAbout::OnMouseInput(sMouseState *m_mouse)
{
    list->OnMouseInput(m_mouse);
}