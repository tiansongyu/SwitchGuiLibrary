#pragma once
#include "guis/gui.hpp"
#include "widgets/button.hpp"
class GuiMain : public Gui
{
public:
    GuiMain();
    ~GuiMain();

    void Update();
    void Draw();
    virtual void OnKeyBoardInput(KeyBoard state)override;
    virtual void OnMouseInput(sMouseState* mouse)override;
    void add();
private:
    Button* button_one;
    int tmp;
};