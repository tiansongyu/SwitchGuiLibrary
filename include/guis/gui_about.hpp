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
    virtual void Draw();
    virtual void OnKeyBoardInput(KeyBoard state)override;
    virtual void OnMouseInput(sMouseState* mouse)override;

private:
    List* list;
};