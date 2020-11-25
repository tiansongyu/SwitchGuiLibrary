#pragma once

#include <string>
#include <vector>

#include"guis/gui.hpp"
#include "widgets/list.hpp"


class GuiAbout : public Gui
{
public:
    GuiAbout();
    ~GuiAbout();

    void Update();
    void Draw();
    virtual void OnKeyBoardInput(KeyBoard state)override;
    virtual void OnMouseInput(sMouseState* mouse)override;
    void Add_first();
    void Add_second();
    void Add_third();

private:
    List* list;
    int tmp_one;
    int tmp_two;
    int tmp_three;
};