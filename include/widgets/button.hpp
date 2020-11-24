#include <switch.h>

#include <string>
#include <functional>

#include "widgets/widget.hpp"

class Button:public Widget
{
public:
    Button(uint32_t x,uint32_t y,uint32_t w ,uint32_t h,std::string _stext);
    ~Button();

    virtual void Draw(Gui* gui) override;
    virtual void OnKeyBoardInput(KeyBoard keystate)override;
    virtual void OnMouseInput(sMouseState* mouse)override;


    void SetInputAction(std::function<void(Gui* gui)> action);
    inline std::string GetText();

private:
    bool IsClip(uint32_t x, uint32_t y);

    uint32_t x,y,w,h;
    std::string stext;
    
    std::function<void(Gui* gui)> action;

};